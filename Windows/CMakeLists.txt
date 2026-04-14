cmake_minimum_required(VERSION 3.10)

project(Program)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

add_executable(Program ../src/Color_Detection.cpp)

target_include_directories(Program PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(Program PRIVATE ${OpenCV_LIBS})
add_executable(OpenCVTest
    ../src/OpenCV.cpp
)
target_include_directories(OpenCVTest PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(OpenCVTest PRIVATE ${OpenCV_LIBS})