//
// Created by bigbywolf on 7/16/18.
//

#ifndef TM4C_CMAKE_LEDTASK_H
#define TM4C_CMAKE_LEDTASK_H


#include <cstdint>
#include <thread.hpp>

class LedTask : public cpp_freertos::Thread{
public:

    LedTask(uint16_t StackDepth, UBaseType_t Priority) ;
    void Run() override ;
};


#endif //TM4C_CMAKE_LEDTASK_H
