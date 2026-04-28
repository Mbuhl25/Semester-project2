cmake_minimum_required(VERSION 3.5)
project(ur_rtde_cmake_example)

include_directories(includes/eigen-3.4.1)
find_package(ur_rtde REQUIRED)
<<<<<<< HEAD
add_executable(ur_rtde_cmake_example pose_trans.cpp)
=======
<<<<<<< HEAD
<<<<<<< HEAD
add_executable(ur_rtde_cmake_example testy-westy.cpp)
=======
add_executable(ur_rtde_cmake_example pose_trans.cpp)
>>>>>>> gunse
=======
add_executable(ur_rtde_cmake_example call_position.cpp)
>>>>>>> d0557c1 (nothing important)
>>>>>>> 38b839ac3a8cbe4d5595632383b18701b531d97d
target_link_libraries(ur_rtde_cmake_example PRIVATE ur_rtde::rtde)