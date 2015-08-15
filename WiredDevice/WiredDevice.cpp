#include "WiredDevice.h"

WiredDevice::WiredDevice(unsigned char address)
        : deviceAddress(deviceAddress) {
}

unsigned char WiredDevice::getDeviceAddress() {
    return deviceAddress;
}

void WiredDevice::setDeviceAddress(unsigned char deviceAddress) {
    this->deviceAddress = deviceAddress;
}
