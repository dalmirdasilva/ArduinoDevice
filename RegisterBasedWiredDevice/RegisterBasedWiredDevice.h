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
#include <RegisterBasedDevice.h>

class RegisterBasedWiredDevice: public RegisterBasedDevice, public WiredDevice {

    const static unsigned char MAX_RETRIES_ON_READING = 10;

public:

    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
    RegisterBasedWiredDevice(unsigned char address);

    /**
     * Reads values from the device, starting by the reg register.
     *
     * @param reg           The register number.
     * @param buf           The buffer where to place read bytes.
     *                      MSB become LSB inside buffer.
     * @param len           How many bytes to read. Up to 32 on most Arduino boards.
     * @return              If >= 0: How many bytes were read. Possible it will be less than len.
     *                      If < 0: Error code:
     *                      <ul>
     *                          <li>-1: data too long to fit in rx buffer</li>
     *                          <li>-2: received NACK on transmit of address</li>
     *                          <li>-3: received NACK on transmit of data</li>
     *                          <li>-4: other error</li>
     *                          <li>-5: timeout</li>
     *                      </ul>
     */
    int readRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len);

    /**
     * Writes a sequence of values to a sequence of registers, starting by the reg address.
     *
     * @param reg           The register number.
     * @param buf           The buffer.
     * @param len           Buffer length.
     * @return              The result of Wire.endTransmission().
     */
    unsigned char writeRegisterBlock(unsigned char reg, unsigned char *buf, unsigned char len);
};

#endif /* __ARDUINO_DRIVER_REGISTER_BASED_WIRED_DEVICE_H__ */
