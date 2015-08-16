/**
 * Arduino - Register Based Wire Device
 *
 * RegisterBasedWireDevice.cpp
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__
#define __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__ 1

#define EEPROM_BASED_WIRED_DEVICE_AFTER_WRITE_DELAY     5

#include <WiredDevice.h>

class EepromBasedWiredDevice: public WiredDevice {

    const static char MAX_RETRIES_ON_READING = 0x7f;

    unsigned char addressSize;
    bool endianness;

public:

    enum {
        LITTLE_ENDIAN = 0x00,
        BIG_ENDIAN = 0x02
    } Endianness;

    /**
     * Public constructor
     * 
     * @param deviceAddress         The wire address.
     * @param addressSize           How long is the internal device addresses.
     * @param endianness            The endianness.
     */
    EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize, unsigned char endianness);

    /**
     * Public constructor
     *
     * @param deviceAddress         The wire address.
     * @param addressSize           How long is the internal device addresses.
     */
    EepromBasedWiredDevice(unsigned char deviceAddress, unsigned char addressSize);

    /**
     * Public constructor
     *
     * @param deviceAddress         The wire address.
     */
    EepromBasedWiredDevice(unsigned char deviceAddress);

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
     * Sends the address MSB fist.
     *
     * @param address
     * @param buf
     * @param len
     */
    void readBlock(unsigned int address, unsigned char* buf, int len);

    /**
     * Sets the address size.
     *
     * @param addressSize
     */
    void setAddressSize(unsigned char addressSize);

    /**
     * Gets the address size.
     *
     * @returm addressSize
     */
    unsigned char getAddressSize();
};

#endif /* __ARDUINO_DRIVER_EEPROM_BASED_WIRED_DEVICE_H__ */
