set(LIB_NAME tiva_driver)

file(GLOB SOURCES "*.cpp" "*.c" "*.h" )

add_library(${LIB_NAME} ${SOURCES})

target_link_libraries(${LIB_NAME}
        ${TIVAWARE_PATH}/driverlib/gcc/libdriver.a ${TIVAWARE_PATH}/usblib/gcc/libusb.a
        )

# Add dependency to the program of linker script during linking stage
set_target_properties(${LIB_NAME} PROPERTIES
        LINK_DEPENDS ${PROJECT_SOURCE_DIR}/ldscripts/${MCU}.lds
        )

