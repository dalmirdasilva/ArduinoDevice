
#include "WiredDevice.h"

WiredDevice::WiredDevice(unsigned char address) {
    this->address = address;
}

unsigned char WiredDevice::getAddress() {
    return address;
}

void WiredDevice::setAddress(unsigned char address) {
    this->address = address;
}
