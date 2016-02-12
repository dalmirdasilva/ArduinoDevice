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
    Wire.write(buf, len);
    Wire.endTransmission();
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
}

int EepromBasedWiredDevice::readBlock(unsigned int address, unsigned char* buf, int len) {
    char tries = MAX_RETRIES_ON_READING;
    int i;
    unsigned char last = len - 1;
    Wire.beginTransmission(getDeviceAddress());
    for (i = addressSize; i > 0; i--) {
        Wire.write((unsigned char) (address >> ((i - 1) * 8)) & 0xff);
    }
    char status = Wire.endTransmission();
    if (status != 0) {
        return -(status);
    }
    delay(EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY);
    Wire.requestFrom((int) getDeviceAddress(), len);
    while (!Wire.available() && --tries > 0) {
        delayMicroseconds(1);
    }
    if (tries <= 0) {
        return -5;
    }
    int r = 0;
    for (i = 0; i < len && Wire.available(); i++) {
        r = Wire.read();
        if (r < 0) {
            break;
        }
        buf[(endianness == BIG_ENDIAN) ? last - i : i] = r & 0xff;
    }
    return i;
}

void EepromBasedWiredDevice::setAddressSize(char addressSize) {
    this->addressSize = addressSize;
}

char EepromBasedWiredDevice::getAddressSize() {
    return addressSize;
}
