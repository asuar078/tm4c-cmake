file(GLOB SOURCES "*.cpp" "*.c" "*.h")

add_library(smbus ${SOURCES})
target_link_libraries(smbus tiva_utils)
