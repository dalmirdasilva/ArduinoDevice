/**
 * Arduino - Register Based Wire Device
 *
 * RegisterBasedWireDevice.cpp
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_REGISTER_BASED_WIRED_DEVICE_H__
#define __ARDUINO_DRIVER_REGISTER_BASED_WIRED_DEVICE_H__ 1

#include <WiredDevice.h>

class RegisterBasedWiredDevice : public WiredDevice {

    const static unsigned char MAX_RETRIES_ON_READING = 10;
    
public:

    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
     RegisterBasedWiredDevice(unsigned char address);
    
    /**
     * Configures a register.
     *
     * @param reg           The register number.
     * @param mask          The mask to be used.
     * @param d             The value to be used.
     */
    void configureRegisterBits(unsigned char reg, unsigned char mask, unsigned char d);
    
    /**
     * Writes a value to a register.
     *
     * @param reg           The register number.
     * @param d             The value to be used.
     */
    unsigned char writeRegister(unsigned char reg, unsigned char d);
    
    /**
     * Reades a value from a register.
     *
     * @param reg           The register number.
     * @return              The register value.
     */
    int readRegister(unsigned char reg);
};

#endif /* __ARDUINO_DRIVER_REGISTER_BASED_WIRED_DEVICE_H__ */
