
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

#include "FromVectorToRobot.h"
#include "KinematicsMath.h"
#include "IndernetForChads.h" 

GripperConnection gripper;
Kinematics kinematics;
// Connect to robot
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

// Global waypoints
std::vector<double> winkelright = {-0.01, 0.0067, 0, 0, 0, 1.57};
std::vector<double> parrallel_correct_grip_point = {0.228327, -0.284797, 0.0367402, -0.63357, 3.06338, -0.00483968};
std::vector<double> perpendicular_correct_grip_point = {0.225974, -0.281095, 0.0379604, -1.69162, -2.61414, 0.00921666};


// Helper functions
void move_parrallel_to_work_start() {
rtde_control.moveJ({-4.35057, -1.88214, 2.16936, -1.85505, -1.57, 0.000107484}, 0.5, 0.3);
}

void move_perpendicular_to_work_start() {
    rtde_control.moveJ({-4.35058, -1.88214, 2.16935, -1.85515, -1.56999, 1.57}, 0.5, 0.3);
}

void move_parrallel_grip_point() {
    rtde_control.moveL(parrallel_correct_grip_point, 0.5, 0.3);
}

void move_perpendicular_grip_point() {
    rtde_control.moveL(perpendicular_correct_grip_point, 0.5, 0.3);
}

// Manipulation functions
void FromVectorToRobot::MoveU(){
    
    // Back to Neutral Position
    move_parrallel_to_work_start();
    move_parrallel_grip_point();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 1.57};
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, 1.57};

    // Pose transformations
    std::vector<double> turn_U = kinematics.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> upwards = kinematics.pose_trans(parrallel_correct_grip_point, move_up_10);

    gripper.gripperOpen();

    // Moves
    rtde_control.moveL(turn_U, speed, acceleration);
    gripper.gripperOpen();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    

    rtde_control.moveL(upwards, speed, acceleration);
    

}

void FromVectorToRobot::MoveUPrime(){

    // Back to neutral position
    move_parrallel_to_work_start();
    move_parrallel_grip_point();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, -1.57};
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, -1.57};

    // Pose Transformations
    std::vector<double> turn_U = kinematics.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> upwards = kinematics.pose_trans(parrallel_correct_grip_point, move_up_10);

    // Move commands
    rtde_control.moveL(turn_U, speed, acceleration);
    rtde_control.moveL(upwards, speed, acceleration);
    
}



void FromVectorToRobot::MoveD(){
    
}

void FromVectorToRobot::MoveDPrime(){

}



void FromVectorToRobot::MoveR(){

    move_perpendicular_to_work_start();
    move_perpendicular_grip_point();
    
    std::vector<double> place_tcp_right = {0, -0.02, 0, 0, 0, 0};
    std::vector<double> turned_r = {0.217449, -0.309183, 0.0347184, -0.840372, -1.4144, -0.956589};
    std::vector<double> ten_cm_back_z = {0, 0, -0.1, 0, 0, 0};

    std::vector<double> move_right_side = kinematics.pose_trans(perpendicular_correct_grip_point, place_tcp_right);
    std::vector<double> get_free_from_cube = kinematics.pose_trans(turned_r, ten_cm_back_z);

    rtde_control.moveL(move_right_side, speed, acceleration);
    rtde_control.moveL(turned_r, speed, acceleration);
    rtde_control.moveL(get_free_from_cube, speed, acceleration);
}

void FromVectorToRobot::MoveRPrime(){


    move_perpendicular_to_work_start();
    move_perpendicular_grip_point();
    
    std::vector<double> place_tcp_right = {0, -0.02, 0, 0, 0, 0};
    std::vector<double> turned_r = {0.217449, -0.309183, 0.0347184, -0.840372, -1.4144, -0.956589};

    
    std::vector<double> ten_cm_back_z = {0, 0, -0.1, 0, 0, 0};
    std::vector<double> ten_cm_forwards_z = {0, 0, 0.1, 0, 0, 0};

    std::vector<double> move_right_side = kinematics.pose_trans(perpendicular_correct_grip_point, place_tcp_right);
    std::vector<double> move_right_side_high = kinematics.pose_trans(move_right_side, ten_cm_back_z);
    std::vector<double> get_free_from_cube = kinematics.pose_trans(turned_r, ten_cm_back_z);


    rtde_control.moveL(move_right_side_high, speed, acceleration);
    rtde_control.moveL(get_free_from_cube, speed, acceleration);
    rtde_control.moveL(turned_r, speed, acceleration);
    rtde_control.moveL(move_right_side, speed, acceleration);

}



void FromVectorToRobot::MoveL(){
    move_perpendicular_to_work_start();
    move_perpendicular_grip_point();

    std::vector<double> place_tcp_left = {0, 0.02, 0, 0, 0, 0};
    std::vector<double> turned_l = {0.247648, -0.289841, 0.0320401, -0.840372, -1.4144, -0.956589};
    std::vector<double> ten_cm_back_z = {0, 0, -0.1, 0, 0, 0};

    std::vector<double> move_left_side = kinematics.pose_trans(perpendicular_correct_grip_point, place_tcp_left);
    std::vector<double> move_left_side_high = kinematics.pose_trans(move_left_side, ten_cm_back_z);
    std::vector<double> get_free_from_cube = kinematics.pose_trans(turned_l, ten_cm_back_z);

    rtde_control.moveL(move_left_side, speed, acceleration);
    rtde_control.moveL(turned_l, speed, acceleration);
    rtde_control.moveL(get_free_from_cube, speed, acceleration);
}

void FromVectorToRobot::MoveLPrime(){
    move_perpendicular_to_work_start();
    move_perpendicular_grip_point();

    std::vector<double> place_tcp_left = {0, 0.02, 0, 0, 0, 0};
    std::vector<double> turned_l = {0.247648, -0.289841, 0.0320401, -0.840372, -1.4144, -0.956589};
    std::vector<double> ten_cm_back_z = {0, 0, -0.1, 0, 0, 0};

    std::vector<double> move_left_side = kinematics.pose_trans(perpendicular_correct_grip_point, place_tcp_left);
    std::vector<double> move_left_side_high = kinematics.pose_trans(move_left_side, ten_cm_back_z);
    std::vector<double> get_free_from_cube = kinematics.pose_trans(turned_l, ten_cm_back_z);

    rtde_control.moveL(move_left_side_high, speed, acceleration);
    rtde_control.moveL(get_free_from_cube, speed, acceleration);
    rtde_control.moveL(turned_l, speed, acceleration);
    rtde_control.moveL(move_left_side, speed, acceleration);
}



void FromVectorToRobot::MoveF(){
 
    move_parrallel_to_work_start();
    move_parrallel_grip_point();
    
    std::vector<double> Move_To_Minusx = {0, -0.02, 0, 0, 0, 0};

    std::vector<double> Move_To_Front = kinematics.pose_trans(parrallel_correct_grip_point, Move_To_Minusx);

    rtde_control.moveL(Move_To_Front, speed, acceleration);

}

void FromVectorToRobot::MoveFPrime(){

}



void FromVectorToRobot::MoveB(){

    move_parrallel_to_work_start();
    move_parrallel_grip_point();

    std::vector<double> Move_To_Back = {0.02, 0, 0, 0, 0, 0};

}

void FromVectorToRobot::MoveBPrime(){

}