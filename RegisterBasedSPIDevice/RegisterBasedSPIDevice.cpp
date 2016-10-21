#include "RegisterBasedSPIDevice.h"
#include <SPI.h>
#include <Arduino.h>

RegisterBasedSPIDevice::RegisterBasedSPIDevice(unsigned char ssPin)
        : SPIDevice(), ssPin(ssPin) {
    pinMode(ssPin, OUTPUT);
    digitalWrite(ssPin, HIGH);
}

unsigned char RegisterBasedSPIDevice::writeRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len) {
    digitalWrite(ssPin, LOW);
    SPI.transfer(reg);
    for (unsigned char i = len; i > 0; i--) {
        Serial.println(",");
        SPI.transfer(buf[i - 1]);
    }
    digitalWrite(ssPin, HIGH);
    return len;
}

int RegisterBasedSPIDevice::readRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len) {
    digitalWrite(ssPin, LOW);
    SPI.transfer(((reg << 1) & 0x7E) | 0x80);
    for (unsigned char i = len; i > 0; i--) {
        Serial.println(".");
        unsigned char c = SPI.transfer(0x00);
        buf[i - 1] = c;
    }
    digitalWrite(ssPin, HIGH);
    return len;
}
