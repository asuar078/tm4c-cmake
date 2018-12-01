/*
 * Task.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: kolban
 */


#include <FreeRTOS.h>
#include <task.h>
#include <string>

#include "Task.h"

namespace freertos {

/**
 * @brief Create an instance of the task class.
 *
 * @param [in] taskName The name of the task to create.
 * @param [in] stackSize The size of the stack.
 * @return N/A.
 */
    Task::Task(char *taskName, uint16_t stackSize, uint8_t priority) {
        m_taskName = taskName;
        m_stackSize = stackSize;
        m_priority = priority;
        m_taskData = nullptr;
        m_handle = nullptr;
    } // Task

    Task::~Task() {
    } // ~Task

/**
 * @brief Suspend the task for the specified milliseconds.
 *
 * @param [in] ms The delay time in milliseconds.
 * @return N/A.
 */
    void Task::delay(int ms) {
        ::vTaskDelay(ms / portTICK_PERIOD_MS);
    } // delay

/**
 * @brief Start an instance of the task.
 *
 * @param [in] taskData Data to be passed into the task.
 * @return N/A.
 */
//	void Task::start(void *taskData) {
////	if (m_handle != nullptr) {
////		ESP_LOGW(tag, "Task::start - There might be a task already running!");
////	}
//		m_taskData = taskData;
//        ::xTaskCreate(reinterpret_cast<void(*)(void*)>(BOUNCE(Task, run)),
//                      m_taskName, m_stackSize, reinterpret_cast<void*>(this), m_priority, &m_handle);
//
//	} // start


/**
 * @brief Stop the task.
 *
 * @return N/A.
 */
    void Task::stop() {
        if (m_handle == nullptr) {
            return;
        }
        xTaskHandle temp = m_handle;
        m_handle = nullptr;
        ::vTaskDelete(temp);
    } // stop

/**
 * @brief Set the stack size of the task.
 *
 * @param [in] stackSize The size of the stack for the task.
 * @return N/A.
 */
    void Task::setStackSize(uint16_t stackSize) {
        m_stackSize = stackSize;
    } // setStackSize

    uint16_t Task::getStackSize(void) {
        return m_stackSize;
    }

/**
 * @brief Set the priority of the task.
 *
 * @param [in] priority The priority for the task.
 * @return N/A.
 */
    void Task::setPriority(uint8_t priority) {
        m_priority = priority;

#ifdef INCLUDE_vTaskPrioritySet
        if(m_handle != nullptr){
            vTaskPrioritySet(m_handle, priority);
        }
#endif
    } // setPriority

    uint8_t Task::getPriority(void) {
        return m_priority;
    }

/**
 * @brief Set the name of the task.
 *
 * @param [in] name The name for the task.
 * @return N/A.
 */
    void Task::setName(char *name) {
        m_taskName = name;
    }

    char *Task::getName(void) {
        return m_taskName;
    }

//    void Task::run(void) {
//        while(1){
//
//        }
//
//    }




    // setName

}
