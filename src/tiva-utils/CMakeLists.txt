file(GLOB SOURCES "*.cpp" "*.c" "*.h")

add_library(tiva_utils STATIC ${SOURCES})
#target_link_libraries(tiva_utils )

