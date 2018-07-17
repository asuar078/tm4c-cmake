//
// Created by bigbywolf on 7/16/18.
//

#include "LedTask.h"

#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <portmacro.h>
#include <projdefs.h>
#include <cstddef>
#include "../peripheral/gpio/GPIO.h"

void LedTask::Run() {

    volatile uint32_t ui32Loop;

    GPIO<SYSCTL_PERIPH_GPIOF, GPIO_PORTF_BASE, GPIO_PIN_2> led0;
    GPIO<SYSCTL_PERIPH_GPIOF, GPIO_PORTF_BASE, GPIO_PIN_1> led1;
//
    led0.output();
    led1.output();

    while(1){

        // Turn on the LED.
        led0.pinWrite(true);
        led1.pinWrite(false);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        // Turn off the LED.
        led0.pinWrite(false);
        led1.pinWrite(true);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

    }

}

LedTask::LedTask(uint16_t StackDepth, UBaseType_t Priority) : Thread(StackDepth, Priority) {}


