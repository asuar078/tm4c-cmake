#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "peripheral/smbus/SMBus.h"
#include "peripheral/gpio/GPIO.h"
#include "task/LedTask.h"

int main(void) {
    LedTask ledTask(256, 3);

    ledTask.Start();

    cpp_freertos::Thread::StartScheduler();

    while (1) {
    }
}
