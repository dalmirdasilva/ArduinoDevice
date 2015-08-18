#include "WiredDevice.h"
#include <Wire.h>

WiredDevice::WiredDevice(unsigned char deviceAddress)
        : deviceAddress(deviceAddress) {
    Wire.begin();
}

unsigned char WiredDevice::getDeviceAddress() {
    return deviceAddress;
}

void WiredDevice::setDeviceAddress(unsigned char deviceAddress) {
    this->deviceAddress = deviceAddress;
}
