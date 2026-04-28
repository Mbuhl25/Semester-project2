cmake_minimum_required(VERSION 3.10)

project(CVProject)

set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Find ur_rtde
find_package(ur_rtde REQUIRED)

# Main executable
add_executable(CVProject
    src/Color_Detection.cpp
    src/Algorithm.cpp
    src/FromVectorToRobot.cpp
    src/GripperConection.cpp
    src/main.cpp 
    src/pose_trans.cpp
)
#Ændre main.cpp til Test_main.cpp hvis i vil kører test side y

# Include directories
add_subdirectory(external/min2phaseCXX)
target_include_directories(CVProject PRIVATE ${CMAKE_SOURCE_DIR}/external/min2phaseCXX/include)
target_link_libraries(CVProject PRIVATE ${OpenCV_LIBS} min2phase ur_rtde::rtde)

target_include_directories(CVProject PUBLIC include)
target_include_directories(CVProject PRIVATE ${CMAKE_SOURCE_DIR}/RTDE_controls/includes/eigen-3.4.1)