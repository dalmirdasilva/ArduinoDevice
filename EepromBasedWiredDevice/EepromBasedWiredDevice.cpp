#include <Arduino.h>
#include <Wire.h>
#include "EepromBasedWiredDevice.h"

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress, char addressSize, unsigned char endianness)
        : WiredDevice(deviceAddress), addressSize(addressSize), endianness(endianness) {
}

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress, char addressSize)
        : EepromBasedWiredDevice(deviceAddress, addressSize, LITTLE_ENDIAN) {
}

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress)
        : EepromBasedWiredDevice(deviceAddress, 0x02) {
}

void EepromBasedWiredDevice::writeBlock(unsigned int address, unsigned char* buf, int len) {
    Wire.beginTransmission(getDeviceAddress());
    for (char i = addressSize; i > 0; i--) {
        Wire.write((unsigned char) (address >> ((i - 1) * 8)) & 0xff);
    }
    for (int i = 0; i < len; i++) {
        Wire.write(buf[i]);
    }
    Wire.endTransmission();
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
}

int EepromBasedWiredDevice::readBlock(unsigned int address, unsigned char* buf, int len) {
    char tries;
    int i;
    unsigned char last = len - 1;
    Wire.beginTransmission(getDeviceAddress());
    for (i = addressSize; i > 0; i--) {
        Wire.write((unsigned char) (address >> ((i - 1) * 8)) & 0xff);
    }
    Wire.endTransmission();
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
    Wire.requestFrom((int) getDeviceAddress(), len);
    for (i = 0; i < len; i++) {
        tries = MAX_RETRIES_ON_READING;
        while (!Wire.available() && --tries > 0) {
            delayMicroseconds(1);
        }
        if (tries == 0) {
            return i;
        }
        buf[(endianness == BIG_ENDIAN) ? last - i : i] = Wire.read();
    }
    return i;
}

void EepromBasedWiredDevice::setAddressSize(char addressSize) {
    this->addressSize = addressSize;
}

char EepromBasedWiredDevice::getAddressSize() {
    return addressSize;
}
