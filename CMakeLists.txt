cmake_minimum_required(VERSION 3.10)

project(CVProject)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Main executable
add_executable(CVProject
    src/Color_Detection.cpp
    src/Test_main.cpp
    src/Algorithm.cpp
    src/main.cpp
)

# Include directories
add_subdirectory(external/min2phaseCXX)
target_include_directories(CVProject PRIVATE ${CMAKE_SOURCE_DIR}/external/min2phaseCXX/include)
target_link_libraries(CVProject PRIVATE ${OpenCV_LIBS} min2phase)

target_include_directories(CVProject PUBLIC include)