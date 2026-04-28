cmake_minimum_required(VERSION 3.5)
project(ur_rtde_cmake_example)

include_directories(includes/eigen-3.4.1)
find_package(ur_rtde REQUIRED)
<<<<<<< HEAD
<<<<<<< HEAD
add_executable(ur_rtde_cmake_example testy-westy.cpp)
=======
add_executable(ur_rtde_cmake_example pose_trans.cpp)
>>>>>>> gunse
=======
add_executable(ur_rtde_cmake_example call_position.cpp)
>>>>>>> d0557c1 (nothing important)
target_link_libraries(ur_rtde_cmake_example PRIVATE ur_rtde::rtde)