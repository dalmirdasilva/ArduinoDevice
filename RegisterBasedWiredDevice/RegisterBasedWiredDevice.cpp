#include <Arduino.h>
#include <Wire.h>
#include "RegisterBasedWiredDevice.h"

RegisterBasedWiredDevice::RegisterBasedWiredDevice(unsigned char address)
        : WiredDevice(address) {
}

void RegisterBasedWiredDevice::configureRegisterBits(unsigned char reg, unsigned char mask, unsigned char d) {
    unsigned char n;
    n = readRegister(reg);
    n &= ~(mask);
    n |= d & mask;
    writeRegister(reg, n);
}

unsigned char RegisterBasedWiredDevice::writeRegisterBlock(unsigned char reg, unsigned char *buff, unsigned char len) {
    Wire.beginTransmission(getDeviceAddress());
    Wire.write(reg);
    Wire.write(buff, len);
    return Wire.endTransmission();
}

int RegisterBasedWiredDevice::readRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len) {
    char tries = MAX_RETRIES_ON_READING;
    unsigned char i;
    Wire.beginTransmission(getDeviceAddress());
    Wire.write(reg);
    char status = Wire.endTransmission(false);
    if (status != 0) {
        return -(status);
    }
    Wire.requestFrom(getDeviceAddress(), len);
    while (!Wire.available() && --tries > 0) {
        delayMicroseconds(1);
    }
    if (tries == 0) {
        return -5;
    }
    for (i = 0; i < len && Wire.available(); i++) {
        buf[i] = Wire.read();
    }
    return i;
}

unsigned char RegisterBasedWiredDevice::writeRegister(unsigned char reg, unsigned char d) {
    return writeRegisterBlock(reg, &d, 1);
}

int RegisterBasedWiredDevice::readRegister(unsigned char reg) {
    unsigned char c;
    int r = readRegisterBlock(reg, &c, 1);
    if (r < 0) {
        return r;
    }
    return (int) c;
}
