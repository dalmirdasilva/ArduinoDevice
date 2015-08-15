/**
 * Arduino - Wired Device
 *
 * WiredDevice.cpp
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_WIRED_DEVICE_H__
#define __ARDUINO_DRIVER_WIRED_DEVICE_H__ 1

class WiredDevice {
    
    unsigned char deviceAddress;
    
public:
    
    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
     WiredDevice(unsigned char deviceAddress);
     
     /**
      * Gets the device address.
      * 
      * @return address
      */ 
     unsigned char getDeviceAddress();
     
     /**
      * Sets the device address.
      * 
      * @param address      The device address.
      */
     void setDeviceAddress(unsigned char deviceAddress);
};

#endif /* __ARDUINO_DRIVER_WIRED_DEVICE_H__ */
