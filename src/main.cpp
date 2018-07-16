#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include <array>
#include <FreeRTOS.h>
#include <vector>
#include "peripheral/smbus/SMBus.h"


// Composition
//template <typename T>
//class GPIO {
//public:
//    GPIO(uint32_t peripheral_port, uint32_t port, uint8_t pin){
//        blink.begin(peripheral_port, port, pin);
//    }
//    void write(bool on){
//        blink.pinWrite(on);
//    }
//
//private:
//    T blink;
//
//};
//
//class Blink {
//public:
//    void begin(uint32_t peripheral_port, uint32_t port, uint8_t pin)
//    {
//        m_pin = pin;
//        m_port = port;
//
//        // Enable the GPIO port that is used for the on-board LED.
//        SysCtlPeripheralEnable(peripheral_port);
//
//        // Check if the peripheral access is enabled.
//        while(!SysCtlPeripheralReady(peripheral_port)) {}
//
//        GPIOPinTypeGPIOOutput(port, pin);
//    }
//
//    void pinWrite(bool on) {
//        if (on)
//            GPIOPinWrite(m_port, m_pin, m_pin);
//        else
//            GPIOPinWrite(m_port, m_pin, 0);
//    }
//
//private:
//    uint32_t m_port;
//    uint8_t m_pin;
//};

template <typename Derived>
class GPIO {
public:
    void init(void){
        auto& derived = static_cast<Derived&>(*this);
        derived.begin();
    }
    void write(bool on){
        auto& derived = static_cast<Derived&>(*this);
        derived.pinWrite(on);
    }
};

template <uint32_t peripheral_port, uint32_t port, uint8_t pin>
class Blink : public GPIO<Blink<peripheral_port, port, pin>> {
public:
    void begin(void)
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

private:
    friend class GPIO<Blink>;
};

template <uint32_t peripheral_port, uint32_t port, uint8_t pin>
class Mock_Blink : public GPIO<Mock_Blink<peripheral_port, port, pin>> {
public:
    void begin(void)
    {
        return;
    }

    void pinWrite(bool on) {
        return;
    }

private:
    friend class GPIO<Mock_Blink>;
};

// Virtual
class x_gpio {
public:
    x_gpio(uint32_t peripheral, uint32_t port, uint8_t pin) :
            m_port(port), m_pin(pin), m_peripheral_port(peripheral) {}

            virtual ~x_gpio() {}

    virtual void pinWrite(bool on) = 0;

protected:
    uint32_t m_port;
    uint8_t m_pin;
    uint32_t m_peripheral_port;
};


class Flash : public x_gpio {
public:
    Flash(uint32_t peripheral_port, uint32_t port, uint8_t pin) : x_gpio(peripheral_port, port, pin)
    {
        // Enable the GPIO port that is used for the on-board LED.
        SysCtlPeripheralEnable(m_peripheral_port);

        // Check if the peripheral access is enabled.
        while(!SysCtlPeripheralReady(m_peripheral_port)) {}

        GPIOPinTypeGPIOOutput(port, pin);
    }

    void pinWrite(bool on) {
        if (on)
            GPIOPinWrite(m_port, m_pin, m_pin);
        else
            GPIOPinWrite(m_port, m_pin, 0);
    }
};

//// Regular class(SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_1)
//class Blink {
//public:
//    Blink(uint32_t peripheral_port, uint32_t port, uint8_t pin) : m_port(port), m_pin(pin)
//    {
//        // Enable the GPIO port that is used for the on-board LED.
//        SysCtlPeripheralEnable(peripheral_port);
//
//        // Check if the peripheral access is enabled.
//        while(!SysCtlPeripheralReady(peripheral_port)) {}
//
//        GPIOPinTypeGPIOOutput(port, pin);
//    }
//
//    void pinWrite(bool on) {
//        if (on)
//            GPIOPinWrite(m_port, m_pin, m_pin);
//        else
//            GPIOPinWrite(m_port, m_pin, 0);
//    }
//
//private:
//    uint32_t m_port;
//    uint8_t m_pin;
//};

int main(void)
{
    volatile uint32_t ui32Loop;

    //std::vector<int> v(3) ;
    //std::array<int, 3> ar {1, 2, 3};

    //SMBus bus(1);
    //bus.getI();

    //Blink led0(SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_1);
    GPIO<Blink<SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_0>> led0;
    GPIO<Blink<SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_1>> led1;

    GPIO<Mock_Blink<SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_1>> mock_led;

    Flash flash(SYSCTL_PERIPH_GPION, GPIO_PORTN_BASE, GPIO_PIN_1);

    led0.init();
    led1.init();

    //
    // Loop forever.
    //
    while(1)
    {
        // Turn on the LED.
        led0.write(true);
        led1.write(false);
        flash.pinWrite(true);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }

        // Turn off the LED.
        led0.write(false);
        led1.write(true);

        // Delay for a bit.
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++)
        {
        }
    }
}
