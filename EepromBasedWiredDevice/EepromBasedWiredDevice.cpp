#include <Arduino.h>
#include <Wire.h>
#include "EepromBasedWiredDevice.h"

EepromBasedWiredDevice::EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize)
        : WiredDevice(deviceAddress), addressSize(addressSize) {
}

void EepromBasedWiredDevice::writeBlock(unsigned int address, unsigned char* buf,
        int len) {
    Wire.beginTransmission(getDeviceAddress());
    for (unsigned char i = addressSize - 1; i >= 0; i--) {
        Wire.write((unsigned char) (address >> (i * 8)) & 0xff);
    }
    for (int i = 0; i < len; i++) {
        Wire.write(buf[i]);
    }
    Wire.endTransmission();
    delay(5);
}

void EepromBasedWiredDevice::readBlock(unsigned int address, unsigned char* buf,
        int len) {
    Wire.beginTransmission(getDeviceAddress());
    for (unsigned char i = addressSize - 1; i >= 0; i--) {
        Wire.write((unsigned char) (address >> (i * 8)) & 0xff);
    }
    Wire.endTransmission();
    Wire.requestFrom((int) getDeviceAddress(), len);
    for (int i = 0; i < len; i++) {
        while (!Wire.available())
            ;
        buf[i] = Wire.read();
    }
}
