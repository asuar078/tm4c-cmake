cmake_minimum_required(VERSION 3.8.2)
project(linux_blinky)

# Some arbitrary hand-maintained version
set(PROJECT_MAJOR_VERSION 1)
set(PROJECT_MINOR_VERSION 0)
set(PROJECT_PATCH_VERSION 0)
set(PROJECT_VERSION  ${PROJECT_MAJOR_VERSION}.${PROJECT_MINOR_VERSION}.${PROJECT_PATCH_VERSION})
set(CMAKE_PROJECT_NAME "${CMAKE_PROJECT_NAME}.${PROJECT_VERSION}")

message(STATUS "")
message(STATUS "Running ${CMAKE_COMMAND} ${CMAKE_VERSION} on ${CMAKE_PROJECT_NAME} v${PROJECT_VERSION}" )

set(CMAKE_BUILD_TYPE Debug)

if(${CMAKE_BUILD_TYPE} MATCHES TESTING)
    message(STATUS "Building test")
    add_subdirectory(test)
endif()

#Toolchain file
include(toolchain/tm4c129.cmake)

#Tivaware files
set(TIVAWARE_PATH "/home/bigbywolf/Applications/tivaware")
include_directories(${TIVAWARE_PATH})
#include_directories(/home/bigbywolf/Applications/gcc-arm-none-eabi-5_4-2016q3/arm-none-eabi/include)

include_directories(includes/)
include_directories(third-party/FreeRTOS/include)
include_directories(third-party/FreeRTOS/portable/GCC/ARM_CM4F)

add_subdirectory(third-party/FreeRTOS)

#Source files
file(GLOB SOURCES "src/*.c" "src/*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a freertos
)

# define objcopy macro
macro(OBJCOPY_FILE EXE_NAME)
    set(FO ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}.bin)
    set(FI ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME})
    message(STATUS ${FO})
    add_custom_command(
            OUTPUT ${FO}
            COMMAND ${CMAKE_OBJCOPY}
            ARGS -O binary ${FI} ${FO}
            DEPENDS ${FI}
    )
    get_filename_component(TGT "${EXE_NAME}" NAME)
    add_custom_target("target-objcopy_${TGT}" ALL DEPENDS ${FO} VERBATIM)
    get_directory_property(extra_clean_files ADDITIONAL_MAKE_CLEAN_FILES)
    set_directory_properties(
            PROPERTIES
            ADDITIONAL_MAKE_CLEAN_FILES "${extra_clean_files};${FO}"
    )
    set_source_files_properties("${FO}" PROPERTIES GENERATED TRUE)
endmacro(OBJCOPY_FILE)

# set the objcopy for binary file
objcopy_file(${CMAKE_PROJECT_NAME})

set(FLASH_EXECUTABLE "/home/bigbywolf/Applications/tivaware/lm4tools/lm4flash/lm4flash")
ADD_CUSTOM_TARGET("flash" DEPENDS ${CMAKE_PROJECT_NAME}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}.bin
        COMMAND ${FLASH_EXECUTABLE} ${CMAKE_PROJECT_NAME}.bin
        )

set(SIZE_CMD "arm-none-eabi-size")
ADD_CUSTOM_TARGET("size" DEPENDS ${CMAKE_PROJECT_NAME}
        COMMAND ${SIZE_CMD} ${CMAKE_PROJECT_NAME}
        )
