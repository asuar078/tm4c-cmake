//
// Created by bigbywolf on 7/17/18.
//

#include "SMBusManager.h"

#include <string.h>

#include <inc/hw_memmap.h>
#include "inc/hw_i2c.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/interrupt.h>
#include "driverlib/debug.h"

#include "FreeRTOS.h"
#include "queue.h"

namespace smbus {

#ifdef PART_TM4C123GH6PM

    static const uint8_t NUM_OF_I2C = 4;
    static const Buspins MCU_I2C[] = {

            /* i2c_periph, periph_port, scl_config, sda_config, port_base, scl_pin, sda_pin, i2c_base*/
            {SYSCTL_PERIPH_I2C0, SYSCTL_PERIPH_GPIOB, GPIO_PB2_I2C0SCL, GPIO_PB3_I2C0SDA, GPIO_PORTB_BASE,
                    GPIO_PIN_2, GPIO_PIN_3, I2C0_BASE},

            {SYSCTL_PERIPH_I2C1, SYSCTL_PERIPH_GPIOA, GPIO_PA6_I2C1SCL, GPIO_PA7_I2C1SDA, GPIO_PORTA_BASE,
                    GPIO_PIN_6, GPIO_PIN_7, I2C1_BASE},

            {SYSCTL_PERIPH_I2C2, SYSCTL_PERIPH_GPIOE, GPIO_PE4_I2C2SCL, GPIO_PE5_I2C2SDA, GPIO_PORTE_BASE,
                    GPIO_PIN_4, GPIO_PIN_5, I2C2_BASE},

            {SYSCTL_PERIPH_I2C3, SYSCTL_PERIPH_GPIOD, GPIO_PD0_I2C3SCL, GPIO_PD1_I2C3SDA, GPIO_PORTD_BASE,
                    GPIO_PIN_0, GPIO_PIN_1, I2C3_BASE},
    };

#else
#error "microcontroller not supported"
#endif


    template<I2CBus i2c_bus, SMBusMode busMode>
    SMBusManager<i2c_bus, busMode>::SMBusManager() : m_i2c_bus(i2c_bus), m_busMode(busMode) {

    }

    template<I2CBus i2c_bus, SMBusMode busMode>
    SMBusManager<i2c_bus, busMode>::~SMBusManager() {

    }

    template<I2CBus i2c_bus, SMBusMode busMode>
    bool SMBusManager<i2c_bus, busMode>::begin() {

        static_assert(i2c_bus > NUM_OF_I2C, "not valid i2c bus");

        // The I2C0 peripheral must be enabled before use.
        SysCtlPeripheralEnable(MCU_I2C[m_i2c_bus].i2c_periph);

        // GPIO port needs to be enabled so these pins can
        // be used.
        SysCtlPeripheralEnable(MCU_I2C[m_i2c_bus].periph_port);

        GPIOPinConfigure(MCU_I2C[m_i2c_bus].scl_config);
        GPIOPinConfigure(MCU_I2C[m_i2c_bus].sda_config);

        // Select the I2C function for these pins.  This function will also
        // configure the GPIO pins pins for I2C operation, setting them to
        // open-drain operation with weak pull-ups.  Consult the data sheet
        // to see which functions are allocated per pin.
        GPIOPinTypeI2CSCL(MCU_I2C[m_i2c_bus].port_base, MCU_I2C[m_i2c_bus].scl_pin);
        GPIOPinTypeI2C(MCU_I2C[m_i2c_bus].port_base, MCU_I2C[m_i2c_bus].sda_pin);

        // Enable interrupts to the processor.
        IntMasterEnable();

        switch (busMode) {
            case SMBusMode::master:
                enableMaster();
                break;
            case SMBusMode::slave:
                enableSlave();
                break;
        }

        return 0;
    }

//    void SMBusManager::enableSlave() {
//
//        SMBusSlaveInit(&smBus, MCU_I2C[m_i2c_bus].i2c_base);
//        SMBusSlaveIntEnable(&smBus);
//
//        /* set primary slave address */
//        SMBusSlaveAddressSet(&smBus, 0, SMART_BATTERY_CHARGER_ADDR);
//        /* set secondary slave address */
//        SMBusSlaveAddressSet(&smBus, 1, SMBUS_DEVICE_DEFAULT_ADDR);
//    }
//
//    void SMBusManager::enableMaster() {
//
//        SMBusMasterInit(&smBus, MCU_I2C[m_i2c_bus].i2c_base, SysCtlClockGet());
//        SMBusMasterIntEnable(&smBus);
//    }
//
//    void SMBusManager::disableSlave(){
//        I2CSlaveDisable(smBus.ui32I2CBase);
//        I2CSlaveIntDisable(smBus.ui32I2CBase);
//    }
//
//    void SMBusManager::disableMaster(){
//        I2CMasterDisable(smBus.ui32I2CBase);
//        I2CMasterIntDisable(smBus.ui32I2CBase);
//    }
//
//    I2CBus SMBusManager::getI2CBus(void) {
//        return m_i2c_bus;
//    }
//
//    SMBusMode SMBusManager::getbusMode(void) {
//        return m_busMode;
//    }
//
//    void SMBusManager::changeBusMode(SMBusMode mode){
//
//        if(mode != m_busMode){
//            m_busMode = mode;
//
//            if(mode == SMBusMode::master){
//                disableSlave();
//                enableMaster();
//            }
//            else{
//                disableMaster();
//                enableSlave();
//            }
//        }
//    }
//
//    SMBusError SMBusManager::masterWrite(MasterOperation &op){
//        if(m_busMode != SMBusMode::master){
//            return SMBusError::MASTER_OPERATION_AS_SLAVE;
//        }
//
//        if(op.pec){
//            SMBusPECEnable(&smBus);
//        }
//        tSMBusStatus stat = SMBusMasterByteWordWrite(&smBus, op.targetAddr, op.command, op.data, op.size);
//        return static_cast<SMBusError>(stat);
//    }
//
//    SMBusError SMBusManager::masterRead(MasterOperation &op){
//        if(m_busMode != SMBusMode::master){
//            return SMBusError::MASTER_OPERATION_AS_SLAVE;
//        }
//
//        if(op.pec){
//            SMBusPECEnable(&smBus);
//        }
//        tSMBusStatus stat = SMBusMasterByteWordRead(&smBus, op.targetAddr, op.command, op.data, op.size);
//        return static_cast<SMBusError>(stat);
//    }







//    const char *SMBusManager::statusToString(tSMBusStatus status) {
//
//        switch (status) {
//
//            case SMBUS_OK:
//                return "OK";
//            case SMBUS_TIMEOUT:
//                return "Master detected bus timeout from slav";
//            case SMBUS_PERIPHERAL_BUSY:
//                return "The I2C peripheral is currently in use";
//            case SMBUS_BUS_BUSY:
//                return "The I2C bus is currently in use";
//            case SMBUS_ARB_LOST:
//                return "Bus arbitration was lost (master mode)";
//            case SMBUS_ADDR_ACK_ERROR:
//                return "In master mode, the address was NAK'd";
//            case SMBUS_DATA_ACK_ERROR:
//                return "Data transfer was NAK'd by receiver";
//            case SMBUS_PEC_ERROR:
//                return "PEC mismatch occurred";
//            case SMBUS_DATA_SIZE_ERROR:
//                return "Data size error has occurred";
//            case SMBUS_MASTER_ERROR:
//                return "Error occurred in the master ISR";
//            case SMBUS_SLAVE_ERROR:
//                return "Error occurred in the slave ISR";
//            case SMBUS_SLAVE_QCMD_0:
//                return "Slave transaction is Quick Command with data value 0.";
//            case SMBUS_SLAVE_QCMD_1:
//                return "Slave transaction is Quick Command with data value 1.";
//            case SMBUS_SLAVE_FIRST_BYTE:
//                return "The first byte has been received";
//            case SMBUS_SLAVE_ADDR_PRIMARY:
//                return "Primary address was detected";
//            case SMBUS_SLAVE_ADDR_SECONDARY:
//                return "Secondary address was detected";
//            case SMBUS_TRANSFER_IN_PROGRESS:
//                return "A transfer is currently in progress";
//            case SMBUS_TRANSFER_COMPLETE:
//                return "The last active transfer is complete";
//            case SMBUS_SLAVE_NOT_READY:
//                return "A slave transmit has been requested, but is not ready (TX buffer not set).";
//            case SMBUS_FIFO_ERROR:
//                return "A master receive operation did not receive enough data from the slave. ";
//        }
//        return "unknown";
//    }

}
