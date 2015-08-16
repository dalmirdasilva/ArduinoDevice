#include <Arduino.h>
#include <Wire.h>
#include "EepromBasedWiredDevice.h"

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize, unsigned char endianness)
        : WiredDevice(deviceAddress), addressSize(addressSize), endianness(endianness) {
}

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize)
        : EepromBasedWiredDevice(deviceAddress, addressSize, LITTLE_ENDIAN) {
}

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress)
        : EepromBasedWiredDevice(deviceAddress, 0x02) {
}

void EepromBasedWiredDevice::writeBlock(unsigned int address, unsigned char* buf, int len) {
    Wire.beginTransmission(getDeviceAddress());
    for (unsigned char i = addressSize - 1; i >= 0; i--) {
        Wire.write((unsigned char) (address >> (i * 8)) & 0xff);
    }
    for (int i = 0; i < len; i++) {
        Wire.write(buf[i]);
    }
    Wire.endTransmission();
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
}

void EepromBasedWiredDevice::readBlock(unsigned int address, unsigned char* buf, int len) {
    char tries;
    unsigned char last = len - 1;
    Wire.beginTransmission(getDeviceAddress());
    for (unsigned char i = addressSize - 1; i >= 0; i--) {
        Wire.write((unsigned char) (address >> (i * 8)) & 0xff);
    }
    Wire.endTransmission();
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
    Wire.requestFrom((int) getDeviceAddress(), len);
    for (int i = 0; i < len; i++) {
    	tries = MAX_RETRIES_ON_READING;
        while (!Wire.available() && --tries > 0) {
            delayMicroseconds(1);
        }
        if (tries == 0) {
            return;
        }
        buf[(endianness == BIG_ENDIAN) ? last - i : i] = Wire.read();
    }
}

void EepromBasedWiredDevice::setAddressSize(unsigned char addressSize) {
    this->addressSize = addressSize;
}

unsigned char EepromBasedWiredDevice::getAddressSize() {
    return addressSize;
}
