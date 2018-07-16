//
// Created by bigbywolf on 7/13/18.
//

#ifndef LINUX_BLINKY_SMBUS_H
#define LINUX_BLINKY_SMBUS_H

#include <cstdint>

enum class smbus_mode {
    master,
    slave
};

template< uint32_t i2c_base, uint32_t bus_clock, smbus_mode mode = smbus_mode::master >
class SMBus {

public:
    SMBus(int t_i) : i(t_i) {

    }

    int begin();

    int getI(){
        return i;
    }

private:
    int i;

};


#endif //LINUX_BLINKY_SMBUS_H
