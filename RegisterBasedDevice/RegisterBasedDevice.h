/**
 * Arduino - Register Based Device
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_REGISTER_BASED_DEVICE_H__
#define __ARDUINO_DRIVER_REGISTER_BASED_DEVICE_H__ 1

class RegisterBasedDevice {

public:

    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
    RegisterBasedDevice();

    /**
     * Configures a register.
     *
     * @param reg           The register number.
     * @param mask          The mask to be used.
     * @param d             The value to be used.
     */
    void configureRegisterBits(unsigned char reg, unsigned char mask,
            unsigned char d);

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
     *                      if < 0:
     *                          -1: data too long to fit in transmit buffer
     *                          -2: received NACK on transmit of address
     *                          -3: received NACK on transmit of data
     *                          -4: other error
     *                          -5: Timeout (max retries)
     */
    int readRegister(unsigned char reg);

    /**
     * Reads values from the device, starting by the reg register.
     *
     * @param reg           The register number.
     * @param buf           The buffer where to place read bytes.
     *                      MSB become LSB inside buffer.
     * @param len           How many bytes to read.
     * @return              If >= 0: How many bytes were read.
     *                      If < 0: Error code:
     *                      <ul>
     *                          <li>-1: data too long to fit in transmit buffer</li>
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

#endif /* __ARDUINO_DRIVER_REGISTER_BASED_DEVICE_H__ */
