//
// Created by bigbywolf on 7/16/18.
//

#ifndef TM4C_CMAKE_GPIO_H
#define TM4C_CMAKE_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>

template <uint32_t peripheral_port, uint32_t port, uint8_t pin>
class GPIO {
public:
    void output(void)
    {
        // Enable the GPIO port that is used for the on-board LED.
        SysCtlPeripheralEnable(peripheral_port);

        // Check if the peripheral access is enabled.
        while(!SysCtlPeripheralReady(peripheral_port)) {}

        GPIOPinTypeGPIOOutput(port, pin);
    }

    void pinWrite(bool on) {
        if (on)
            GPIOPinWrite(port, pin, pin);
        else
            GPIOPinWrite(port, pin, 0);
    }
};


#endif //TM4C_CMAKE_GPIO_H
