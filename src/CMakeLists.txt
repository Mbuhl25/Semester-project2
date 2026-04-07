cmake_minimum_required(VERSION 4.1)
project(Program)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(Program Color_Detection.cpp)

target_link_libraries(Program ${OpenCV_LIBS})
