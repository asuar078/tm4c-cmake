
#include "LedTask.h"

#include <cstdint>
#include "priorities.h"
#include "utils/uartstdio.h"
#include "../drivers/rgb.h"

#define LED_TOGGLE_DELAY        250

namespace task {

// [G, R, B] range is 0 to 0xFFFF per color.
    static uint32_t g_pui32Colors[3] = {0x0000, 0x0000, 0x0000};
    static uint8_t g_ui8ColorsIndx;


    LedTask::LedTask(char *taskName, uint16_t stackSize, uint8_t priority) : Task(taskName, stackSize, priority) {

    }

    void LedTask::start(void *taskData){
        m_taskData = taskData;
        ::xTaskCreate(reinterpret_cast<void(*)(void*)>(BOUNCE(LedTask, run)),
                      m_taskName, m_stackSize, reinterpret_cast<void*>(this), m_priority, &m_handle);
    }

    void LedTask::run(void ){

        // Initialize the GPIOs and Timers that drive the three LEDs.
        RGBInit(1);
        RGBIntensitySet(0.3f);

        // Turn on the Green LED
        g_ui8ColorsIndx = 0;
        g_pui32Colors[g_ui8ColorsIndx] = 0x8000;
        RGBColorSet(g_pui32Colors);

        // Print the current loggling LED and frequency.
        UARTprintf("\nLed %d is blinking. [R, G, B]\n", g_ui8ColorsIndx);
        UARTprintf("Led blinking frequency is %d ms.\n", (LED_TOGGLE_DELAY * 2));

        portTickType ui32WakeTime;
        uint32_t ui32LEDToggleDelay;
        uint8_t i8Message;

        // Initialize the LED Toggle Delay to default value.
        ui32LEDToggleDelay = LED_TOGGLE_DELAY;

        // Get the current tick count.
        ui32WakeTime = xTaskGetTickCount();

        while(1){

            // Turn on the LED.
            RGBEnable();

            // Wait for the required amount of time.
            vTaskDelayUntil(&ui32WakeTime, ui32LEDToggleDelay / portTICK_RATE_MS);

            // Turn off the LED.
            RGBDisable();

            // Wait for the required amount of time.
            vTaskDelayUntil(&ui32WakeTime, ui32LEDToggleDelay / portTICK_RATE_MS);
        }

    }


}

