cmake_minimum_required(VERSION 3.5)
project(ur_rtde_cmake_example)

include_directories(includes/eigen-3.4.1)
find_package(ur_rtde REQUIRED)
add_executable(ur_rtde_cmake_example pose_trans.cpp)
target_link_libraries(ur_rtde_cmake_example PRIVATE ur_rtde::rtde)