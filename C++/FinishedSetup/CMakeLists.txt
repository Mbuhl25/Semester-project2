cmake_minimum_required(VERSION 3.10)

project(CVProject)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Add executable
add_executable(CVProject
    source/main.cpp
    source/Kociemba.cpp
    source/CV2ForCPP.cpp
)

# Include directories
target_include_directories(CVProject PUBLIC include)

# Link OpenCV
target_link_libraries(CVProject ${OpenCV_LIBS})