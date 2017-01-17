#include "RegisterBasedSPIDevice.h"
#include <SPI.h>
#include <Arduino.h>

RegisterBasedSPIDevice::RegisterBasedSPIDevice(unsigned char ssPin)
        : SPIDevice(), ssPin(ssPin) {
    pinMode(ssPin, OUTPUT);
    digitalWrite(ssPin, HIGH);
}

unsigned char RegisterBasedSPIDevice::writeRegisterBlock(unsigned char reg,
        unsigned char *buf, unsigned char len) {
    SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));
    digitalWrite(ssPin, LOW);
    SPI.transfer(reg);
    for (unsigned char i = 0; i < len; i++) {
        SPI.transfer(buf[i]);
    }
    digitalWrite(ssPin, HIGH);
    SPI.endTransaction();
    return len;
}

int RegisterBasedSPIDevice::readRegisterBlock(unsigned char reg, unsigned char *buf,
        unsigned char len) {
    int n = len;
    if (len > 0) {
        
        // Why?
        len--;
        SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV4, MSBFIRST, SPI_MODE0));
        digitalWrite(ssPin, LOW);
        SPI.transfer(reg);
        for (unsigned char i = 0; i < len; i++) {
            buf[i] = SPI.transfer(reg);
        }
        buf[len] = SPI.transfer(0);
        digitalWrite(ssPin, HIGH);
        SPI.endTransaction();
    }
    return n;
}
