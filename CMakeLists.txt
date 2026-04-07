cmake_minimum_required(VERSION 3.10)

project(CVProject)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Main executable
add_executable(CVProject
    src/CppCubeSolver.cpp
)

# Color detection executable
add_executable(ColorDetect
    src/magnus.cpp
)

# Camera test executable
add_executable(OpenCVTest
    src/OpenCV.cpp
)

# Include directories
add_subdirectory(external/min2phaseCXX)
target_include_directories(CVProject PRIVATE ${CMAKE_SOURCE_DIR}/external/min2phaseCXX/include)
target_link_libraries(CVProject PRIVATE ${OpenCV_LIBS} min2phase)
target_link_libraries(ColorDetect PRIVATE ${OpenCV_LIBS})
target_link_libraries(OpenCVTest PRIVATE ${OpenCV_LIBS})

