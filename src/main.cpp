#include <stdint.h>
#include <stdbool.h>
#include <driverlib/rom.h>
#include <driverlib/pin_map.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"

#include "peripheral/smbus/SMBus.h"
#include "peripheral/gpio/GPIO.h"
#include "task/LedTask.h"
#include "bus_manager/smbus/SMBusManager.h"
#include "task/SMBusTask.h"

/*
 * [100%] Built target tm4c_cmake.1.0.0
   text	   data	    bss	    dec	    hex	filename
  71505	   2488	  31232	 105225	  19b09	tm4c_cmake.1.0.0
 */

//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}

task::LedTask led(nullptr);

int main(void)
{

    // Set the clocking to run at 50 MHz from the PLL.
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                   SYSCTL_OSC_MAIN);

    // Initialize the UART and configure it for 115,200, 8-N-1 operation.
    ConfigureUART();

    // Print demo introduction.
    UARTprintf("\n\nWelcome to the EK-TM4C123GXL FreeRTOS Demo!\n");

    led.start(nullptr);

     led.run();

    vTaskStartScheduler();

    while (1)
    {
    }
}
