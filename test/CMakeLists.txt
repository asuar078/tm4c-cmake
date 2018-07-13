
cmake_minimum_required(VERSION 3.8.2)
project (blinky_test)

include_directories(../third-party/Catch2/single_include)

file(GLOB SRC "*.cpp")

add_executable (${PROJECT_NAME} ${SRC})