//
// Created by bigbywolf on 7/17/18.
//

#ifndef TM4C_CMAKE_SMBUSMANAGER_H
#define TM4C_CMAKE_SMBUSMANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include <utils/smbus.h>

namespace smbus {

    static const uint8_t SMBUS_HOST_ADDR = 0x08;
    static const uint8_t SMART_BATTERY_CHARGER_ADDR = 0x09;
    static const uint8_t SMART_BATTERY_SELECTOR_ADDR = 0x0A;
    static const uint8_t SMART_BATTERY_ADDR = 0x0B;
    static const uint8_t SMBUS_ALERT_RESPONSE = 0x0C;
    static const uint8_t SMBUS_DEVICE_DEFAULT_ADDR = 0x61;

    static const uint8_t BUFFER_SIZE = (4);

    enum I2CBus {
        i2c_0 = 0, i2c_1, i2c_2, i2c_3, i2c_4, i2c_5, i2c_6, i2c_7, i2c_8, i2c_9
    };

    enum class SMBusMode {
        master = 0, slave
    };

    struct Buspins {
        uint32_t i2c_periph;
        uint32_t periph_port;
        uint32_t scl_config;
        uint32_t sda_config;
        uint32_t port_base;
        uint8_t scl_pin;
        uint8_t sda_pin;
        uint32_t i2c_base;
    };

    struct SMBusItem {
        SMBusMode smbusMode;
        I2CBus i2cBus;
        tSMBusStatus status;
        uint8_t slaveCommand;
        uint8_t *rx_buf;
        uint8_t *tx_buf;
        uint8_t calculatedCRC;
        uint8_t receivedCRC;
    };

    struct MasterOperation {
        uint8_t targetAddr = 0;
        uint8_t command = 0;
        uint8_t* data = nullptr;
        uint8_t size = 0;
        bool pec = false;
        bool block = false;

        void reset(void){
                targetAddr = 0;
                command = 0;
                data = nullptr;
                size = 0;
                pec = false;
                block = false;
        }
    };

    enum SMBusError {
        SMBUS_OK = 0,               // General "OK" return code
        SMBUS_TIMEOUT,              // Master detected bus timeout from slave
        SMBUS_PERIPHERAL_BUSY,      // The I2C peripheral is currently in use
        SMBUS_BUS_BUSY,             // The I2C bus is currently in use
        SMBUS_ARB_LOST,             // Bus arbitration was lost (master mode)
        SMBUS_ADDR_ACK_ERROR,       // In master mode, the address was NAK'd
        SMBUS_DATA_ACK_ERROR,       // Data transfer was NAK'd by receiver
        SMBUS_PEC_ERROR,            // PEC mismatch occurred
        SMBUS_DATA_SIZE_ERROR,      // Data size error has occurred
        SMBUS_MASTER_ERROR,         // Error occurred in the master ISR
        SMBUS_SLAVE_ERROR,          // Error occurred in the slave ISR
        SMBUS_SLAVE_QCMD_0,         // Slave transaction is Quick Command with
        // data value 0.
                SMBUS_SLAVE_QCMD_1,         // Slave transaction is Quick Command with
        // data value 1.
                SMBUS_SLAVE_FIRST_BYTE,     // The first byte has been received
        SMBUS_SLAVE_ADDR_PRIMARY,   // Primary address was detected
        SMBUS_SLAVE_ADDR_SECONDARY, // Secondary address was detected
        SMBUS_TRANSFER_IN_PROGRESS, // A transfer is currently in progress
        SMBUS_TRANSFER_COMPLETE,    // The last active transfer is complete
        SMBUS_SLAVE_NOT_READY,      // A slave transmit has been requested, but is
        // not ready (TX buffer not set).
                SMBUS_FIFO_ERROR,           // A master receive operation did not receive
        // enough data from the slave.

        MASTER_OPERATION_AS_SLAVE   // Tried to perform a master read/write in slave mode

    };

    template <I2CBus i2c_bus = I2CBus::i2c_0, SMBusMode busMode= SMBusMode::slave>
    class SMBusManager {

    public:
        SMBusManager();

        ~SMBusManager();

        bool begin();

        I2CBus getI2CBus(void);
        SMBusMode getbusMode(void);

        void changeBusMode(SMBusMode mode);

        SMBusError masterWrite(MasterOperation &op);
        SMBusError masterRead(MasterOperation &op);

//        void isr_smbus_slave(void);
//        void isr_smbus_master(void);

        const static char *statusToString(tSMBusStatus status);

    protected:
        int initBus();
        void enableSlave();
        void enableMaster();

        void disableSlave();
        void disableMaster();

        I2CBus m_i2c_bus;
        SMBusMode m_busMode;

        tSMBus smBus;

        uint8_t rxBuf[BUFFER_SIZE] = {0};
        uint8_t txBuf[BUFFER_SIZE] = {0};

//            QueueHandle_t m_smbus_q {nullptr};

    };
}

#endif //TM4C_CMAKE_SMBUSMANAGER_H
