/**
 * Arduino - Register Based Wire Device
 *
 * RegisterBasedWireDevice.cpp
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__
#define __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__ 1

#include <WiredDevice.h>

class EepromBasedWiredDevice: public WiredDevice {

    unsigned char addressSize;

public:

    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
    EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize);

    /**
     * Writes a block of bytes separately by pages to the device.
     *
     * @param address
     * @param buf
     * @param len
     */
    void writeBlock(unsigned int address, unsigned char* buf, int len);

    /**
     * Reads a block of bytes from the device.
     *
     * @param address
     * @param buf
     * @param len
     */
    void readBlock(unsigned int address, unsigned char* buf, int len);
};

#endif /* __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__ */
