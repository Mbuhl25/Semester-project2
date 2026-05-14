cmake_minimum_required(VERSION 3.10)

project(CVProject)

set(CMAKE_CXX_STANDARD 17)

# -------------------------
# Find packages
# -------------------------
find_package(OpenCV REQUIRED)
find_package(ur_rtde REQUIRED)

# -------------------------
# Executable
# -------------------------
add_executable(CVProject
    src/FromVectorToRobot.cpp
    src/ManipolationOfRing.cpp
    src/Color_Detection.cpp
    src/KinematicsMath.cpp
    src/main.cpp
)

# -------------------------
# External libraries
# -------------------------
add_subdirectory(external/min2phaseCXX)

# -------------------------
# Include directories
# -------------------------
target_include_directories(CVProject
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/min2phaseCXX/include
    ${CMAKE_SOURCE_DIR}/RTDE_controls/includes/eigen-3.4.1
    ${CMAKE_SOURCE_DIR}/include
)

# -------------------------
# Find Pylon
# -------------------------
execute_process(
    COMMAND /home/mbbu/Downloads/pylon-26.04.1_linux-x86_64_setup/bin/pylon-config --cflags
    OUTPUT_VARIABLE PYLON_CFLAGS
)

execute_process(
    COMMAND /home/mbbu/Downloads/pylon-26.04.1_linux-x86_64_setup/bin/pylon-config --libs
    OUTPUT_VARIABLE PYLON_LIBS
)

string(STRIP "${PYLON_CFLAGS}" PYLON_CFLAGS)
string(STRIP "${PYLON_LIBS}" PYLON_LIBS)

separate_arguments(PYLON_CFLAGS_LIST UNIX_COMMAND "${PYLON_CFLAGS}")
separate_arguments(PYLON_LIBS_LIST UNIX_COMMAND "${PYLON_LIBS}")

target_compile_options(CVProject PRIVATE ${PYLON_CFLAGS_LIST})

# -------------------------
# Link libraries
# -------------------------
target_link_libraries(CVProject
    PRIVATE
    ${OpenCV_LIBS}
    ${PYLON_LIBS_LIST}
    min2phase
    ur_rtde::rtde
)