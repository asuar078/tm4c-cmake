#include "LedTask.h"

#include <cstdint>
#include "priorities.h"
#include "utils/uartstdio.h"
#include "../drivers/rgb.h"

#include <stdint.h>
#include <stdbool.h>
#include <driverlib/rom.h>
#include <driverlib/pin_map.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define LED_TOGGLE_DELAY 250
#define RED_LED GPIO_PIN_1
#define RED_LED GPIO_PIN_1
#define BLUE_LED GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
#define BLUE_LED GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

namespace task
{

// [G, R, B] range is 0 to 0xFFFF per color.
// static uint32_t g_pui32Colors[3] = {0x0000, 0x0000, 0x0000};
// static uint8_t g_ui8ColorsIndx;

LedTask::LedTask(char *taskName, uint16_t stackSize, uint8_t priority) : Task(taskName, stackSize, priority)
{
}

void LedTask::start(void *taskData)
{
    m_taskData = taskData;
    ::xTaskCreate(reinterpret_cast<void (*)(void *)>(BOUNCE(LedTask, run)),
                  m_taskName, m_stackSize, reinterpret_cast<void *>(this), m_priority, &m_handle);
}

void LedTask::run(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED);

    // Print the current loggling LED and frequency.
    UARTprintf("\nLed is blinking. [R, G, B]\n");
    UARTprintf("Led blinking frequency is %d ms.\n", (250 * 2));

    while (1)
    {
        // Turn on the LED
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, GREEN_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);

        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, BLUE_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);

        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED, RED_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
    }
}


} // namespace task
