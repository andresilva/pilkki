#pragma once

#include <optional>
#include <string>
#include <memory>

class Serial final {
private:
    struct Impl_;
    std::unique_ptr<Impl_> impl_;
public:
    explicit Serial(const std::string& name);
    Serial(const Serial&) = delete;
    Serial(Serial&&);
    ~Serial();

    void write(const void * data, size_t len);
    size_t read(void * data, size_t maxLen);

    bool good();

    static std::optional<std::string> autodetect();
};
