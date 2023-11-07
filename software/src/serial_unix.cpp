#include "serial.hpp"

#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include <iostream>
#include <string_view>

#include <stdexcept>

struct Serial::Impl_ {
    int fd;

    Impl_(int descriptor): fd(descriptor) {
        if (fd<=0) {
            throw std::runtime_error("Failed to open Serial");
        }
    }

    Impl_(const Impl_&) = delete;

    Impl_(Impl_&& impl): fd(impl.fd) {
        impl.fd = 0;
    }

    ~Impl_() {
        if (fd>0) {
            ::close(fd);
        }
        fd = 0;
    }
};

Serial::Serial(const std::string& name):
    impl_(new Impl_(::open(name.c_str(), O_RDWR | O_NOCTTY)))
{
    auto fd = impl_->fd;

    struct termios tty;
    memset (&tty, 0, sizeof(tty));

    /* Error Handling */
    if ( tcgetattr ( fd, &tty ) != 0 ) {
        throw std::runtime_error("Failed to tcgetattr: " + std::string(strerror(errno)));
    }

    // /* Set Baud Rate */
    // cfsetospeed (&tty, (speed_t)B9600);
    // cfsetispeed (&tty, (speed_t)B9600);

    /* Setting other Port Stuff */
    tty.c_iflag &= ~(INLCR | ICRNL); //<
    tty.c_iflag |= IGNPAR | IGNBRK; //<
    tty.c_oflag &= ~(OPOST | ONLCR | OCRNL); //<
    tty.c_cflag &= ~(PARENB | PARODD | CSTOPB | CSIZE | CRTSCTS); //< Make 8n1, ... , no flow control
    tty.c_cflag |= CLOCAL | CREAD | CS8; //< Ignore control lines, turn on READ, ...
    tty.c_lflag &= ~(ICANON | ISIG | ECHO); //<

    tty.c_cc[VMIN]   =  0;                  // read does block
    tty.c_cc[VTIME]  =  5;                  // 0.5 seconds read timeout

    // /* Make raw */
    cfmakeraw(&tty);

    // /* Flush Port, then applies attributes */
    // tcflush( fd, TCIFLUSH );
    if ( tcsetattr ( fd, TCSAFLUSH, &tty ) != 0) {
        throw std::runtime_error("Failed to tcsetattr: " + std::string(strerror(errno)));
    }
}

Serial::Serial(Serial&& s): impl_(std::move(s.impl_)) {
    s.impl_ = nullptr;
}

Serial::~Serial() {}

void Serial::write(const void * data, size_t len) {
    size_t n = len;
    while(n > 0) {
        int res = ::write(impl_->fd, data, n);
        if ( res<0 ) {
            throw std::runtime_error("Failed to write: " + std::string(strerror(errno)));
        }
        if (!res) {
            throw std::runtime_error("Failed to write: wrote nothing this time");
        }
        n -= res;
    }
}

size_t Serial::read(void * data, size_t maxLen) {
    int res = ::read(impl_->fd, data, maxLen);
    if ( res<0 ) {
        throw std::runtime_error("Failed to read: " + std::string(strerror(errno)));
    }
    return res;
}
