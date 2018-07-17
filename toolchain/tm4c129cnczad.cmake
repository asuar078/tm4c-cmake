#Set cross compilation information
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(MCU tm4c1294ncpdt)

# GCC toolchain prefix
set(TOOLCHAIN_PREFIX "/home/bigbywolf/Applications/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-")

# add processor specific definitions
add_definitions(
        -DPART_TM4C1294NCPDT
        -DTARGET_IS_TM4C129_RA1
        -Dgcc
        -DARM_MATH_CM4
)

# add processor specific definitions
#add_definitions(-DPART_TM4C123GH6PM)
#add_definitions(-DTARGET_IS_TM4C123_RA1)
#add_definitions(-Dgcc)

# specify the toolchain
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}as)
set(CMAKE_AR ${TOOLCHAIN_PREFIX}ar)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_OBJDUMP ${TOOLCHAIN_PREFIX}objdump)

enable_language(ASM)

# set compiler flags
set(CPU "-mcpu=cortex-m4 -mtune=cortex-m4 -march=armv7e-m ")
set(FPU "-mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")

set(CMAKE_ASM_FLAGS "${CPU} ${FPU} -MD")

set(CMAKE_C_FLAGS "${CPU} ${FPU} -std=gnu99 -Os -Og -ffunction-sections -fdata-sections -MD -Wall -Wextra -pedantic")

set(CMAKE_CXX_FLAGS "${CPU} ${FPU} -Os -Og -ffunction-sections -fdata-sections -MD -Wall -Wextra -pedantic -std=c++14 \
    -fno-exceptions -fno-non-call-exceptions -fno-rtti  -fno-unwind-tables -fno-common -finline-small-functions \
    -findirect-inlining -fno-threadsafe-statics -fno-asynchronous-unwind-tables")


# set linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-gc-sections \
    -Wl,-Map=blink.map \
    -Wl,-T${PROJECT_SOURCE_DIR}//ldscripts/${MCU}.lds -specs=${PROJECT_SOURCE_DIR}/ldscripts/tiva.specs -specs=nosys.specs")

# prevent from running linker during compiler test
set( CMAKE_TRY_COMPILE_TARGET_TYPE  STATIC_LIBRARY )

# search for programs in the build host directories
set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM  NEVER )
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE  ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE  ONLY)

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH
        /home/bigbywolf/Applications/gcc-arm-none-eabi-5_4-2016q3/arm-none-eabi
        )

# cache the flags for use
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "CFLAGS")
set(CMAKE_Cxx_FLAGS "${CMAKE_C_xxFLAGS}" CACHE STRING "CXXFLAGS")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "")
