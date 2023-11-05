
#include "serial.hpp"

#include <windows.h>

#include <cstdint>
#include <cstdbool>
#include <cstring>

#include <iostream>
#include <string_view>

#include <stdexcept>





struct Serial::Impl_ {
    HANDLE h;

    Impl_(HANDLE h_): h(h_) {
        if (h == INVALID_HANDLE_VALUE) {
            throw std::runtime_error("Failed to open Serial");
        }
    }
    Impl_(const Impl_&) = delete;

    Impl_(Impl_&& v_): h(v_.h) {
        v_.h = INVALID_HANDLE_VALUE;
    }

    ~Impl_() {
        if(h) {
            CloseHandle(h);
        }
        h = INVALID_HANDLE_VALUE; //< Just for sure
    }
};

Serial::Serial(const std::string& name):
    impl_(new Impl_(CreateFileA(name.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)))
{
    auto handle = impl_->h;
    if (!FlushFileBuffers(handle)) {
        throw std::runtime_error("Failed to flush serial port buffers");
    }

    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = 1;
    timeouts.ReadTotalTimeoutConstant = 2000;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 1000;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    if (!SetCommTimeouts(handle, &timeouts))
    {
        throw std::runtime_error("Failed to set serial timeouts");
    }

}

Serial::Serial(Serial&& s): impl_(std::move(s.impl_)) {
    s.impl_ = nullptr;
}
Serial::~Serial() {}

void Serial::write(const void * data, size_t len) {
    size_t n = len;
    while(n > 0) {
        DWORD res;
        if (!WriteFile(impl_->h, data, n, &res, nullptr)) {
            throw std::runtime_error("Failed to write: " + std::string(strerror(errno)));
        }
        if (!res) {
            throw std::runtime_error("Failed to write: wrote nothing this time");
        }
        n -= res;
    }
}

size_t Serial::read(void * data, size_t maxLen) {
    DWORD res;
    if(!ReadFile(impl_->h, data, maxLen, &res, nullptr)) {
        throw std::runtime_error("Failed to read: " + std::string(strerror(errno)));
    }
    return res;
}

std::optional<std::string> Serial::autodetect() {
    return std::nullopt;
}
