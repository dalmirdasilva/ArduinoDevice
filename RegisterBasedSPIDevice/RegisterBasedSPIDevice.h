/**

 * Arduino - Register Based SPI Device
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_REGISTER_BASED_SPI_DEVICE_H__
#define __ARDUINO_DRIVER_REGISTER_BASED_SPI_DEVICE_H__ 1

#include <SPIDevice.h>
#include <RegisterBasedDevice.h>

class RegisterBasedSPIDevice: public RegisterBasedDevice, public SPIDevice {

protected:
    unsigned char ssPin;

public:

    /**
     * Public constructor
     * 
     * @param ssPin         The SS pin for the device.
     */
    RegisterBasedSPIDevice(unsigned char ssPin);

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

#endif /* __ARDUINO_DRIVER_REGISTER_BASED_SPI_DEVICE_H__ */
