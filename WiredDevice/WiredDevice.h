/**
 * Arduino - Wired Device
 *
 * WiredDevice.cpp
 *
 * @author Dalmir da Silva <dalmirdasilva@gmail.com>
 */

#ifndef __ARDUINO_DRIVER_WIRED_DEVICE_H__
#define __ARDUINO_DRIVER_WIRED_DEVICE_H__ 1

#include <Wire.h>

class WiredDevice {
    
    unsigned char address;
    
public:
    
    /**
     * Public constructor
     * 
     * @param address       The wire address.
     */
     WiredDevice(unsigned char address);
     
     /**
      * Gets the device address.
      * 
      * @return address
      */ 
     unsigned char getAddress();
     
     /**
      * Sets the device address.
      * 
      * @param address      The device address.
      */
     void setAddress(unsigned char address);
};

#endif /* __ARDUINO_DRIVER_WIRED_DEVICE_H__ */
