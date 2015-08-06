
#include <Arduino.h>
#include "RegisterBasedWiredDevice.h"

RegisterBasedWiredDevice::RegisterBasedWiredDevice(unsigned char address) : WiredDevice(address) {
}

void RegisterBasedWiredDevice::configureRegisterBits(unsigned char reg, unsigned char mask, unsigned char d) {
    unsigned char n;
    n = readRegister(reg);
    n &= ~(mask);
    n |= d & mask;
    writeRegister(reg, n);
}

unsigned char RegisterBasedWiredDevice::writeRegister(unsigned char reg, unsigned char d) {
    Wire.beginTransmission(getAddress());
    Wire.write(reg);
    Wire.write(d);
    return Wire.endTransmission();
}

int RegisterBasedWiredDevice::readRegister(unsigned char reg) {
    char tries = MAX_RETRIES_ON_READING;
    Wire.beginTransmission(getAddress());
    Wire.write(reg);
    char status = Wire.endTransmission(false);
    if (status != 0) {
        return -(status);
    }
    Wire.requestFrom(getAddress(), (unsigned char) 1);
    while (!Wire.available() && --tries > 0) {
        delayMicroseconds(1);
    }
    if (tries == 0) {
        return -5;
    }
    return Wire.read();
}
