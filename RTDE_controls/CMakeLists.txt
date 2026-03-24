cmake_minimum_required(VERSION 3.5)
project(ur_rtde_cmake_example)

find_package(ur_rtde REQUIRED)
<<<<<<< Updated upstream
add_executable(ur_rtde_cmake_example main.cpp)
=======
add_executable(ur_rtde_cmake_example testy_pose.cpp)
>>>>>>> Stashed changes
target_link_libraries(ur_rtde_cmake_example PRIVATE ur_rtde::rtde)