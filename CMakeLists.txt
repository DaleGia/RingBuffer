cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
project(RingBuffer)

# Add the source file containing the RingBuffer class
add_executable(RingBuffer examples/test.cpp)
