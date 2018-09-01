
# Set include path
include_directories (include)
include_directories (portable/GCC/ARM_CM4F )
include_directories (portable/MemMang)

set(SRCS
        croutine.c
        event_groups.c
        list.c
        Queue.c
        tasks.c
        timers.c
        portable/GCC/ARM_CM4F/port.c
        # include the specified heap allocator
        portable/MemMang/heap_2.c
        )


ADD_LIBRARY(freertos ${SRCS})