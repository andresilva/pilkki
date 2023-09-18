
#include <argparse/argparse.hpp>

#include <memory>
#include <fstream>

#include "serial.hpp"

namespace {



std::pair<std::string, std::string> getPair(const std::string_view& line) {
    auto pos = line.find(" ");
    if (pos == std::string::npos) {
        return {std::string(line), {}};
    }
    std::string k {line.substr(0, pos)};
    std::string v {line.substr(pos+1)};
    return {k, v};

}

std::unordered_map<std::string, std::string> parseChipInfo(const std::string& data) {
    size_t pos_start = 0;
    size_t pos_end;
    std::unordered_map<std::string, std::string> res;
    std::string_view dataView{data};
    const std::string_view lineDelim{"\r\n"};

    while ((pos_end = dataView.find(lineDelim, pos_start)) != std::string::npos) {
        std::string_view line = dataView.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + lineDelim.size();
        auto kv = getPair(line);
        res[kv.first] = kv.second;
    }
    return res;
}


class Flasher {
private:
    Serial * serial_;

    void sendCommand_(const std::string& cmd) {
        std::string data = '\n' + cmd + '\n';
        // std::cout<<"send: " << cmd << std::endl;
        serial_->write(data.data(), data.size());
    }

    std::string receiveResult_() {
        char buffer[256];
        std::string res;
        while (res.find("***\r\n") == std::string::npos) {
            size_t len = serial_->read(buffer, sizeof(buffer));
            res += std::string_view(buffer, len);

            if (!len) {
                throw std::runtime_error("Failed to read: no more data\n" + res);
            }
        }
        if(res.find("err") != std::string::npos) {
            throw std::runtime_error("Received error: " + res);
        }
        auto pos = res.find("***\r\n");
        res = res.substr(0, pos);
        // std::cout << "recv:\n" << res << std::endl;
        return res;

    }

    std::string execute_(const std::string& cmd) {
        sendCommand_(cmd);
        return receiveResult_();
    }

public:
    Flasher(Serial * serial): serial_(serial) {
        if (!serial_) {
            throw std::runtime_error("No serial");
        }
    }

    std::string getId() {
        auto info = connect();
        return execute_("id");
    }

    std::string connect() {
        return execute_("connect");
    }

    std::string run() {
        auto info = connect();
        return execute_("run");
    }

    std::string reset(bool hard = false) {
        auto info = connect();
        std::string cmd{"res"};
        if (hard) {
            cmd += " -h";
        }
        return execute_(cmd);
    }

    std::string halt() {
        auto info = connect();
        return execute_("halt");
    }

    struct Payload {
        std::vector<uint8_t> data;
        uint32_t crc;

        uint32_t calculateCRC() {
            const uint32_t POLY = 0xEDB88320;
            uint32_t res = -1;
            for (uint8_t byte: data) {
                res = res ^ byte;
                for (size_t i = 0; i<8; ++i) {
                    if (res&1) {
                        res = (res>>1) ^ POLY;
                    } else {
                        res = res>>1;
                    }
                }
            }
            return ~res;
        }

        bool checkCRC() {
            return crc == calculateCRC();
        }
    };

    Payload read(uint32_t addr, std::optional<uint32_t> len, bool hex) {
        auto info = connect();

        uint32_t payloadLen = 0;
        if (len) {
            payloadLen = *len;
        } else {

            auto infoMap = parseChipInfo(info);
            auto flashSizeIter = infoMap.find("FlashSize");
            if (flashSizeIter == infoMap.end()) {
                throw std::runtime_error("Failed to get flash size");
            }
            payloadLen = std::stoul(flashSizeIter->second, nullptr, 0);
        }

        uint32_t payloadWords = payloadLen >> 2;
        if (payloadLen & 0b11) {
            ++payloadWords;
        }

        std::cout << "Reading " << payloadWords << " words from address 0x" << std::hex << std::setfill('0') << std::setw(8) << addr << std::endl;

        sendCommand_("rd " + std::to_string(addr) + " " + std::to_string(payloadWords));
        uint32_t realFirmwareLen = payloadWords<<2;
        uint32_t realPayloadLen = realFirmwareLen + 8;
        std::vector<uint8_t> data;
        data.reserve(realPayloadLen);
        while (data.size() < realPayloadLen) {
            uint8_t buf[256];
            uint32_t toRead = std::min(sizeof(buf), realPayloadLen - data.size());
            uint32_t didRead = serial_->read(buf, toRead);
            std::copy(buf, buf + didRead, std::back_inserter(data));
        }
        uint32_t crcPayload = *(reinterpret_cast<uint32_t *>(data.data()+realFirmwareLen));
        std::string doneRecord{reinterpret_cast<char *>(data.data()+realFirmwareLen+4), 4};
        if (doneRecord != "Done") {
            throw std::runtime_error("Missing \"Done\" record");
        }
        data.resize(realFirmwareLen);
        Payload res{.data{std::move(data)}, .crc = crcPayload};
        if (!res.checkCRC()) {
            throw std::runtime_error("CRC mismatch");
        }
        return res;
    }

    uint32_t crc(uint32_t addr, std::optional<uint32_t> len) {
        auto info = connect();
        uint32_t regionLen = 0;
        if (len) {
            regionLen = *len;
        } else {

            auto infoMap = parseChipInfo(info);
            auto flashSizeIter = infoMap.find("FlashSize");
            if (flashSizeIter == infoMap.end()) {
                throw std::runtime_error("Failed to get flash size");
            }
            regionLen = std::stoul(flashSizeIter->second, nullptr, 0);
        }

        uint32_t nWords = regionLen >> 2;
        if (regionLen & 0b11) {
            ++nWords;
        }
        auto res = execute_("crc " + std::to_string(addr) + " " + std::to_string(nWords));
        if (res.find("Crc32 = ") != 0) {
            throw std::runtime_error("Failed to get CRC");
        }
        return std::stoul(res.substr(8), nullptr, 0);
    }

    void erase(uint32_t addr, std::optional<uint32_t> pages) {
        auto info = connect();

        auto infoMap = parseChipInfo(info);

        auto flashSizeIter = infoMap.find("FlashSize");
        if (flashSizeIter == infoMap.end()) {
            throw std::runtime_error("Failed to get flash size");
        }
        size_t flashSize = std::stoul(flashSizeIter->second, nullptr, 0);

        auto pageSizeIter = infoMap.find("PageSize");
        if (pageSizeIter == infoMap.end()) {
            throw std::runtime_error("Failed to get page size");
        }
        size_t pageSize = std::stoul(pageSizeIter->second, nullptr, 0);

        size_t maxPages = flashSize / pageSize;
        if (maxPages > 1024) {
            maxPages = 0;
        }
        size_t nPages = pages?(*pages):maxPages;


        if (nPages > maxPages) {
            throw std::runtime_error(
                "Impossible to erase " + std::to_string(nPages)
                + " pages. Maximum: " + std::to_string(maxPages) + "."
            );
        }
        auto loaderRes = execute_("loader");
        // std::cout << "Loader: " << loaderRes << std::endl;
        std::cout << "Erasing " << nPages << " pages (" << nPages * pageSize << " bytes) at"
            << std::hex << std::setw(8) << std::setfill('0') << std::showbase << addr << "..." << std::endl;
        auto eraseRes = execute_("erase " + std::to_string(addr) + " " + std::to_string(nPages));
        // std::cout << "Erase: " << eraseRes << std::endl;
        std::cout << "Erase done." << std::endl;
    }

    void write(std::istream& data, uint32_t addr, std::optional<uint32_t> len) {
        data.seekg(0, std::ios_base::end);
        uint32_t dataLen = data.tellg();
        if (len) {
            dataLen = std::min(dataLen, *len);
        }
        data.seekg(0, std::ios_base::beg);
        uint32_t dataWords = dataLen >> 2;
        if (dataLen & 0b11) {
            ++dataWords;
        }
        Payload p;
        p.data.resize(dataWords<<2, 0);
        data.read(reinterpret_cast<char *>(p.data.data()), dataLen);
        p.crc = p.calculateCRC();


        auto info = connect();

        auto infoMap = parseChipInfo(info);

        auto flashSizeIter = infoMap.find("FlashSize");
        if (flashSizeIter == infoMap.end()) {
            throw std::runtime_error("Failed to get flash size");
        }
        size_t flashSize = std::stoul(flashSizeIter->second, nullptr, 0);

        auto pageSizeIter = infoMap.find("PageSize");
        if (pageSizeIter == infoMap.end()) {
            throw std::runtime_error("Failed to get page size");
        }
        size_t pageSize = std::stoul(pageSizeIter->second, nullptr, 0);

        if (dataLen > flashSize) {
            throw std::runtime_error(
                "Firmware will not fit. Avail " + std::to_string(flashSize) +
                " bytes, needed " + std::to_string(dataLen) + " bytes."
            );
        }

        uint32_t nPages = dataLen / pageSize;
        if (nPages * pageSize < dataLen) {
            ++nPages;
        }

        auto loaderResult = execute_("loader");
        // std::cout << "Loader: " << loaderResult << std::endl;

        auto bufSizeStr = execute_("bufsize");
        // std::cout << "BufSize: " << bufSizeStr << std::endl;
        if (bufSizeStr.find("MaxBuf = ") != 0) {
            throw std::runtime_error("Failed to get buffer size");
        }
        size_t bufSize = std::stoul(bufSizeStr.substr(9), nullptr, 0);
        bufSize <<= 2;
        std::cout << "Erasing..." << std::endl;
        auto eraseResult = execute_("erase " + std::to_string(addr) + " " + std::to_string(nPages));
        // std::cout << "Erase: " << eraseResult << std::endl;
        std::cout << "Erase done, flashing..." << std::endl;

        size_t nParts = dataLen / bufSize;
        if (nParts * bufSize < dataLen) {
            ++nParts;
        }

        size_t written = 0;
        while (written < p.data.size()) {
            size_t packetLen = std::min(p.data.size() - written, bufSize);
            size_t packetWords = packetLen>>2;
            auto flags = std::cout.flags();
            std::cout << "Writing " << packetLen << " bytes at "
                << std::hex << std::setw(8) << std::setfill('0') << std::showbase << (addr+written) << std::endl;
            std::cout.flags(flags);
            auto loadBufResult = execute_("loadbuffer " + std::to_string(packetWords));
            if (loadBufResult.find("Load ready") != 0) {
                std::cout << "LoadBuffer:\n\"" << loadBufResult << "\"" << std::endl;
                throw std::runtime_error("loadbuffer - operation failed");
            }

            serial_->write(p.data.data() + written, packetLen);
            // std::cout << "Wrote " << packetLen << " bytes" << std::endl;
            auto sendBufResult = receiveResult_();
            // std::cout << "Send: " << sendBufResult << std::endl;
            auto writeBufResult = execute_("writebuffer " + std::to_string(addr+written) + " " +std::to_string(packetWords));
            // std::cout << "WriteBuffer: " << writeBufResult << std::endl;
            written += packetWords<<2;
        }

        uint32_t crcReceived = crc(addr, p.data.size());
        if (crcReceived != p.crc) {
            throw std::runtime_error("CRC mismatch");
        }

        std::cout << "Flash written and verified. Have fun!" << std::endl;
        reset();



    }
};



struct BaseArgs: public argparse::Args {
    std::optional<std::string>& port = kwarg("p,port", "Serial port to interact with flasher. Autodetect if not specified.");

    std::shared_ptr<Serial> getSerial() {
        std::optional<std::string> pName;

        if (port) {
            pName = *port;
        } else {
            std::cout << "No port specified, trying to autodetect..." << std::endl;
            pName = Serial::autodetect();
        }

        if (pName) {
            std::cout << "Connecting to port \"" << *pName << "\"" << std::endl;
            return std::make_shared<Serial>(*pName);
        }

        std::cout << "Port was neither specified nor autodetected." << std::endl;
        return nullptr;
    }


};

struct IdCommand: public BaseArgs {
    void welcome() {
        std::cout << "Get SWD Programmer Hardware ID." << std::endl;
    }

    virtual int run() {
        auto serial = getSerial();
        Flasher f{serial.get()};
        std::cout << f.getId() << std::endl;
        return 0;
    }
};

struct ConnectCommand: public BaseArgs {
    void welcome() {
        std::cout << "Connect to the target and halt it." << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        std::cout << f.connect() << std::endl;
        return 0;
    }
};

struct RunCommand: public BaseArgs {
    void welcome() {
        std::cout << "Run the target." << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        f.run();
        return 0;
    }
};

struct HaltCommand: public BaseArgs {
    void welcome() {
        std::cout << "Halt the target." << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        f.halt();
        return 0;
    }
};

struct ResetCommand: public BaseArgs {
    bool& hard = flag("hw,hard", "Hard reset.");
    void welcome() {
        std::cout << "Reset the target (soft/hard)." << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        f.reset(hard);
        return 0;
    }
};

enum class Format {
    BIN,
    HEX,
};

struct IOCommand: public BaseArgs {
    std::string& addr = kwarg("a,addr", "Starting address on the target.").set_default("0x08000000");
protected:
    uint32_t addr_() {
        return std::stoul(addr, nullptr, 0);
    }
};

struct ReadCommand: public IOCommand {
    std::string& output = kwarg("o,output", "Output file name: <filename>.(bin/hex)").set_default("out.bin");
    std::optional<std::string>& length = kwarg("l,length", "Length of the memory region to read (in bytes).");


    void welcome() {
        std::cout << "Read firmware from the target." << std::endl;
    }

    void writeBin(std::ostream& o, Flasher::Payload p) {
        o.write(reinterpret_cast<char *>(p.data.data()), p.data.size());
    }

    void writeHex(std::ostream& o, Flasher::Payload p, uint32_t baseAddr) {
        uint8_t crc = 0;
        bool Header = true;
        uint16_t AddrH, AddrL;
        uint16_t BufSize = 32; //bytes per line
        uint32_t BufShift = 0;
        size_t Len = p.data.size();
        uint8_t * Data = p.data.data();

        while (Len)
        {
            AddrL = baseAddr & 0xFFFF;
            AddrH = (baseAddr >> 16) & 0xFFFF;

            if (AddrL == 0) Header = true;

            if (Header)
            {
                crc = -(6 + (AddrH & 0xFF) + ((AddrH >> 8) & 0xFF));

                o << ":02" << std::setw(4) << std::setfill('0') << std::hex << std::uppercase << 0
                    << "04" << std::setw(4) << AddrH << std::setw(2) << uint32_t(crc) << std::endl;
                Header = false;
                BufSize = 32;
            }
            if (Len < BufSize) BufSize = Len;

            BufShift = 0x10000 - (baseAddr & 0xFFFF);
            if (BufShift < BufSize)
            {
                Header = true;
                BufSize = BufShift;
            }


            o << ":" << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << BufSize
                    << std::setw(4) << AddrL << "00";
            crc = BufSize + (AddrL & 0xFF) + ((AddrL >> 8) & 0xFF);

            for (uint16_t i = 0; i < BufSize; i++)
            {
                o << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << uint32_t(*Data);
                crc += *Data & 0xFF;
                Data++;
                baseAddr++;
                if (Len) Len--;
                if (Len == 0) break;
            }
            o << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << ((-crc) & 0xFF) << std::endl;
        }
        o << ":00000001FF" << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        bool hex = (output.size() > 4) && (output.substr(output.size() - 4) == ".hex");
        auto res = f.read(addr_(), length_(), hex);
        std::ofstream ofs(output);
        if (!ofs.good()) {
            throw std::runtime_error("Failed to open file \"" + output + "\"");
        }
        if (hex) {
            writeHex(ofs, res, addr_());
        } else {
            writeBin(ofs, res);
        }
        return 0;
    }

protected:
    std::optional<uint32_t> length_() {
        if (length) {
            return std::stoul(*length, nullptr, 0);
        }
        return std::nullopt;
    }
};

struct EraseCommand: public IOCommand {
    std::optional<uint32_t>& pages = kwarg("pages", "Number of pages to erase.");
    void welcome() {
        std::cout << "Erase firmware from the target." << std::endl;
    }

    virtual int run () {
        auto serial = getSerial();
        Flasher f{serial.get()};
        f.erase(addr_(), pages);
        return 0;
    }
};

struct WriteCommand: public IOCommand {
    std::string& input = kwarg("i,input", "Input file name: <file_name>.(bin/hex)");
    std::optional<std::string>& length = kwarg("l,length", "Length of the memory region to write (in bytes).");
    void welcome() {
        std::cout << "Write firmware to the target." << std::endl;
    }

    virtual int run() {
        std::ifstream ifs(input);
        if (!ifs.good()) {
            throw std::runtime_error("Failed to open file \"" + input + "\"");
        }
        auto serial = getSerial();
        Flasher f{serial.get()};
        f.write(ifs, addr_(), length_());
        return 0;
    }
protected:
    std::optional<uint32_t> length_() {
        if (length) {
            return std::stoul(*length, nullptr, 0);
        }
        return std::nullopt;
    }
};

struct CRCCommand: public IOCommand {
    std::optional<uint32_t>& length = kwarg("l,length", "Length of the memory region to read (in bytes).");

    void welcome() {
        std::cout << "Calculate CRC32 checksum of memory region on the target." << std::endl;
    }

    virtual int run() {
        auto serial = getSerial();
        Flasher f{serial.get()};
        uint32_t addr = addr_();
        auto res = f.crc(addr, length);
        std::cout << "CRC of ";
        if (length) {
            std::cout << (*length) << " bytes";
        } else {
            std::cout << "available memory";
        }
        std::cout << " starting from 0x" << std::hex << std::setfill('0') << std::setw(8) << addr
            << " is 0x" << res << std::endl;
        return 0;
    }
};

struct AppArgs: public argparse::Args {
    bool &version = flag("v,version", "Print version (of this program).");

    IdCommand& id = subcommand("id");
    ConnectCommand& connect = subcommand("connect");
    HaltCommand& halt = subcommand("halt");
    RunCommand& run = subcommand("run");
    ResetCommand& reset = subcommand("reset");
    ReadCommand& read = subcommand("read");
    EraseCommand& erase = subcommand("erase");
    WriteCommand& write = subcommand("write");
    CRCCommand& crc = subcommand("crc");


    void welcome() {
        std::cout << "Pilkki - SWD Flasher\n\n"
            << "All the following arguments require connection to the hardware part of the SWD flasher\n"
            << "The address and size can be specified in either decimal or hexadecimal format (prefixed with 0x).\n"
            << "Both values must be multiples of a word (4 bytes).\n"
            << std::endl;
    }
};
} // namespace

int main(int argc, char ** argv) {
    AppArgs args{argparse::parse<AppArgs>(argc, argv)};

    if (args.version) {
        std::cout<<"Pilkki (ver. 0.0.1)"<<std::endl;
        return 0;
    }
    try {
        return args.run_subcommands();
    } catch (std::exception& e) {
        std::cout << "ERROR:\n" << e.what() << std::endl;
    }
    return -1;

}
