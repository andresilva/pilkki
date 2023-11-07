
#include "serial.hpp"

#include <libudev.h>


std::optional<std::string> Serial::autodetect() {
    auto udev = udev_new();
    auto enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "tty");
    udev_enumerate_scan_devices(enumerate);
    for (
        auto entry = udev_enumerate_get_list_entry(enumerate);
        entry != nullptr;
        entry = udev_list_entry_get_next(entry)
    ) {
        auto name = udev_list_entry_get_name(entry);
        auto dev = udev_device_new_from_syspath(udev, name);
        auto prop = udev_device_get_property_value(dev, "ID_PATH");
        if (prop != nullptr) {
            return std::string(udev_device_get_devnode(dev));
        }
    }
    return std::nullopt;
}
