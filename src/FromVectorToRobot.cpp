#include "FromVectorToRobot.h"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
//#include "Algorithm.h"
#include "pose_trans.h"
#include <iostream>
#include <sstream> 

//Algorithm alg;

//std::string FromVectorToRobot::VecMove(std::vector<std::string> moves){}



// Connect to robot
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");


Pose_Trans PT;

// Global waypoints
std::vector<double> grip_point = {0.22657, -0.285007, 0.0422215, 0.620214, -3.07384, 0};
std::vector<double> adjust_to_cube = {0.007, 0.0025, 0, 0, 0, 0};
std::vector<double> winkelright = {-0.01, 0.0067, 0, 0, 0, 1.57};
std::vector<double> parrallel_correct_grip_point = PT.pose_trans(grip_point, adjust_to_cube);
std::vector<double> perpendicular_correct_grip_point = PT.pose_trans(parrallel_correct_grip_point, winkelright);


// Helper functions
void move_parrallel_to_work_start(){

rtde_control.moveJ({-4.35057, -1.88214, 2.16936, -1.85505, -1.57, 0.000107484}, 0.5, 0.3);

}

void move_perpendicular_to_work_start(){
    rtde_control.moveJ({-4.35058, -1.88214, 2.16935, -1.85515, -1.56999, 1.57}, 0.5, 0.3);
}

void move_parrallel_grip_point(){

    rtde_control.moveL(parrallel_correct_grip_point, 0.5, 0.3);
}

void move_perpendicular_grip_point(){
    rtde_control.moveL(perpendicular_correct_grip_point, 0.5, 0.3);
}




// Manipulation functions
void FromVectorToRobot::MoveU(){
    // Speed and Acceleration
    double speed = 0.2;
    double acceleration = 0.4;
    
    // Back to Neutral Position
    move_parrallel_to_work_start();
    move_parrallel_grip_point();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 1.57};
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, 1.57};

    // Pose transformations
    std::vector<double> turn_U = PT.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> upwards = PT.pose_trans(parrallel_correct_grip_point, move_up_10);

    // Moves
    rtde_control.moveL(turn_U, speed, acceleration);
    rtde_control.moveL(upwards, speed, acceleration);
    

}

void FromVectorToRobot::MoveUPrime(){
    // Speed and Acceleration
    double speed = 0.2;
    double acceleration = 0.4;

    // Back to neutral position
    move_parrallel_to_work_start();
    move_parrallel_grip_point();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, -1.57};
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, -1.57};

    // Pose Transformations
    std::vector<double> turn_U = PT.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> upwards = PT.pose_trans(parrallel_correct_grip_point, move_up_10);

    // Move commands
    rtde_control.moveL(turn_U, speed, acceleration);
    rtde_control.moveL(upwards, speed, acceleration);
    
}



void FromVectorToRobot::MoveD(){
    
}

void FromVectorToRobot::MoveDPrime(){

}



void FromVectorToRobot::MoveR(){
    // Speed and Acceleration
    double speed = 0.1;
    double acceleration = 0.1;

    move_perpendicular_to_work_start();
    move_perpendicular_grip_point();
    
    std::vector<double> place_tcp_right = {0, -0.02, 0, 0, 0, 0};
    std::vector<double> turned_r = {0.217449, -0.309183, 0.0347184, -0.840372, -1.4144, -0.956589};
    std::vector<double> ten_cm_back_z = {0, 0, -0.1, 0, 0, 0};

    std::vector<double> move_right_side = PT.pose_trans(perpendicular_correct_grip_point, place_tcp_right);
    std::vector<double> get_free_from_cube = PT.pose_trans(turned_r, ten_cm_back_z);

    rtde_control.moveL(move_right_side, speed, acceleration);
    rtde_control.moveL(turned_r, speed, acceleration);
    rtde_control.moveL(get_free_from_cube, speed, acceleration);
}

void FromVectorToRobot::MoveRPrime(){

}



void FromVectorToRobot::MoveL(){

}

void FromVectorToRobot::MoveLPrime(){

}



void FromVectorToRobot::MoveF(){

}

void FromVectorToRobot::MoveFPrime(){

}



void FromVectorToRobot::MoveB(){

}

void FromVectorToRobot::MoveBPrime(){

}



int main(){
    FromVectorToRobot move;
    move.MoveR();


}