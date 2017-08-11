#include <Arduino.h>
#include <Wire.h>
#include "RegisterBasedWiredDevice.h"

RegisterBasedWiredDevice::RegisterBasedWiredDevice(unsigned char address)
        : RegisterBasedDevice(), WiredDevice(address) {
}

unsigned char RegisterBasedWiredDevice::writeRegisterBlock(unsigned char reg, unsigned char *buff, unsigned char len) {
    Wire.beginTransmission(getDeviceAddress());
    Wire.write(reg);
    Wire.write(buff, len);
    return Wire.endTransmission();
}

int RegisterBasedWiredDevice::readRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len) {
    Wire.beginTransmission(getDeviceAddress());
    Wire.write(reg);
    char status = Wire.endTransmission(false);
    if (status != 0) {
        return -(status);
    }
    Wire.requestFrom(getDeviceAddress(), len);
    int read = Wire.available();
    for (int i = 0; i < read; i++) {
        buf[i] = (unsigned char) Wire.read();
    }
    return read;
}
