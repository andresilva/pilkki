#include "serial.hpp"
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/IOBSD.h>
#include <IOKit/IOKitLib.h>

std::optional<std::string> Serial::autodetect() {
    std::optional<std::string> devicePath = std::nullopt;

    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOSerialBSDServiceValue);
    if (!matchingDict) {
        return std::nullopt;
    }

    CFDictionarySetValue(matchingDict, CFSTR(kIOSerialBSDTypeKey), CFSTR(kIOSerialBSDAllTypes));

    io_iterator_t serialPortIterator;
    if (IOServiceGetMatchingServices(MACH_PORT_NULL, matchingDict, &serialPortIterator) != KERN_SUCCESS) {
        return std::nullopt;
    }

    io_object_t modemService;
    while ((modemService = IOIteratorNext(serialPortIterator))) {
        CFTypeRef bsdPathAsCFString = IORegistryEntryCreateCFProperty(modemService, CFSTR(kIOCalloutDeviceKey), kCFAllocatorDefault, 0);
        if (bsdPathAsCFString) {
            char path[512];
            if (CFStringGetCString((CFStringRef)bsdPathAsCFString, path, sizeof(path), kCFStringEncodingUTF8)) {
                std::string deviceString(path);

                // Check if the path contains "usbmodem"
                if (deviceString.find("usbmodem") != std::string::npos) {
                    devicePath = deviceString;
                    CFRelease(bsdPathAsCFString);
                    break;
                }
            }
            CFRelease(bsdPathAsCFString);
        }
        IOObjectRelease(modemService);
    }

    IOObjectRelease(serialPortIterator);
    return devicePath;
}
