////
//// Created by bigbywolf on 7/18/18.
////
//
//#include "SMBusTask.h"
//
//#include "priorities.h"
//#include "../bus_manager/smbus/SMBusManager.h"
//#include <utils/uartstdio.h>
//
//namespace task {
//
//    SMBusTask::SMBusTask(cpp_freertos::Queue &smbusQueue)
//        : Thread(256, PRIORITY_SMBUS_TASK), m_smbusQueue(smbusQueue)
//    {
//    }
//
//    void SMBusTask::Run() {
//
//        bool dequeued ;
//
//        manager::smbus::SMBusItem q_item;
//
//        while(1) {
//
//            dequeued = m_smbusQueue.Dequeue(&q_item);
//
//            UARTprintf("status: ");
//            UARTprintf(manager::smbus::SMBusManager::statusToString(q_item.status));
//            UARTprintf("\n\r");
//
//        }
//    }
//
//
//}
