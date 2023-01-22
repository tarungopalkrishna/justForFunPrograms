cmake_minimum_required(VERSION 3.0.0)
project(kafka_nest VERSION 0.0.0)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE ON)

# message("Hello this is a good test")
include(CTest)
enable_testing()
add_test(test1 kafka_nest COMMAND kafka_nest)



add_executable(kafka_nest src/main.cpp)

# How to write this in CMake?
# find_package(rdkafka++ REQUIRED)
# find_package(Boost REQUIRED COMPONENTS thread system)
target_compile_options(kafka_nest PRIVATE -g -Wall -pg -O0)
target_link_libraries(kafka_nest PRIVATE rdkafka++ rdkafka)
# target_link_libraries(kafka_nest )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
