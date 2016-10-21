#include "SPIDevice.h"
#include <SPI.h>
#include <Arduino.h>
SPIDevice::SPIDevice() {

    Serial.println("aqui");
    SPI.begin();
}
