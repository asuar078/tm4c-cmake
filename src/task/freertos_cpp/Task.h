/*
 * Task.h
 *
 *  Created on: Mar 4, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_TASK_H_
#define COMPONENTS_CPP_UTILS_TASK_H_

#include "FreeRTOS.h"
#include "task.h"

template<class T, class Method, Method m, class ...Params>
static auto bounce(void *priv, Params... params) ->
decltype(((*reinterpret_cast<T *>(priv)).*m)(params...))
{
    return ((*reinterpret_cast<T *>(priv)).*m)(params...);
}

/// Convenience macro to simplify bounce statement usage
#define BOUNCE(c,m) bounce<c, decltype(&c::m), &c::m>

namespace freertos {

    class Task {
    public:
        Task(char *taskName, uint16_t stackSize = 1024, uint8_t priority = 5);

        virtual ~Task();

        void setStackSize(uint16_t stackSize);
        uint16_t getStackSize(void);

        void setPriority(uint8_t priority);
        uint8_t getPriority(void);

        void setName(char *name);
        char* getName(void);

        /**
         * virtual function for starting a task. Use the template below to create the
         * start function. All that needs to be replaced is the Task_Name with the name of the class inheriting.
         * @param taskData
         *  void Task::start(void *taskData) {
                if (m_handle != nullptr) {
                    m_taskData = taskData;
                    ::xTaskCreate(reinterpret_cast<void(*)(void*)>(BOUNCE(Task_Name, run)),
                                  m_taskName, m_stackSize, reinterpret_cast<void*>(this), m_priority, &m_handle);
                }
             } // start
         */
        virtual void start(void *taskData);
        virtual void run(void);

        void stop();
        void delay(int ms);

    protected:
        TaskHandle_t m_handle;
        void *m_taskData;
        char *m_taskName;
        uint16_t m_stackSize;
        uint8_t m_priority;
    };
}

#endif /* COMPONENTS_CPP_UTILS_TASK_H_ */
