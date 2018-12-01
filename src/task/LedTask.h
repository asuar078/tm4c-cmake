/*
 * LedTask.h
 *
 *  Created on: Jul 19, 2018
 *      Author: bigbywolf
 */

#ifndef TASK_LEDTASK_H_
#define TASK_LEDTASK_H_

#include "freertos_cpp/Task.h"

namespace task
{
class LedTask : public freertos::Task
{
  public:
    LedTask(char *taskName, uint16_t stackSize = 1024, uint8_t priority = 5);
    void start(void *taskData);
    void run(void);
};

} /* namespace task */

#endif /* TASK_LEDTASK_H_ */
