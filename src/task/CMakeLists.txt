set(LIB_NAME task)

file(GLOB SOURCES "*.cpp" "*.c" "*.h" "freertos_cpp/*.cpp" "freertos_cpp/*.c" "freertos_cpp/*.h")

add_library(${LIB_NAME} ${SOURCES})
#ADD_DEPENDENCIES(${LIB_NAME}  freertos gpio cpp_utils)

target_link_libraries(${LIB_NAME}
        ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a ${TIVAWARE_PATH}/usblib/gcc/libusb.a
        freertos peripheral tiva_driver
        )

# Add dependency to the program of linker script during linking stage
set_target_properties(${LIB_NAME} PROPERTIES
        LINK_DEPENDS ${PROJECT_SOURCE_DIR}/ldscripts/${MCU}.lds
        )