#include "RegisterBasedDevice.h"

RegisterBasedDevice::RegisterBasedDevice() {
}

void RegisterBasedDevice::configureRegisterBits(unsigned char reg, unsigned char mask, unsigned char d) {
    unsigned char n;
    n = readRegister(reg);
    n &= ~(mask);
    n |= d & mask;
    writeRegister(reg, n);
}

unsigned char RegisterBasedDevice::writeRegister(unsigned char reg, unsigned char d) {
    return writeRegisterBlock(reg, &d, 1);
}

int RegisterBasedDevice::readRegister(unsigned char reg) {
    unsigned char c;
    int r = readRegisterBlock(reg, &c, 1);
    if (r < 0) {
        return r;
    }
    return (int) c;
}
