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
std::vector<double> adjust_to_cube = {0.006, 0.002, 0, 0, 0, 0};
std::vector<double> correct_grip_point = PT.pose_trans(grip_point, adjust_to_cube);


// Helper functions
void move_to_work_start(){

rtde_control.moveJ({-4.35057, -1.88214, 2.16936, -1.85505, -1.57, 0.000107484}, 0.5, 0.3);

}

void move_grip_point(){

    rtde_control.moveL(correct_grip_point, 0.5, 0.3);
}




// Manipulation functions
void FromVectorToRobot::MoveU(){
    
    move_to_work_start();
    move_grip_point();
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 1.57};
    std::vector<double> turn_U = PT.pose_trans(correct_grip_point, ninety_deg_z);
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, 1.57};
    std::vector<double> upwards = PT.pose_trans(correct_grip_point, move_up_10);
    rtde_control.moveL(turn_U, 0.5, 0.3);
    rtde_control.moveL(upwards, 0.5, 0.3);
    

}

void FromVectorToRobot::MoveUPrime(){
    move_to_work_start();
    move_grip_point();
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, -1.57};
    std::vector<double> turn_U = PT.pose_trans(correct_grip_point, ninety_deg_z);
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, -1.57};
    std::vector<double> upwards = PT.pose_trans(correct_grip_point, move_up_10);
    rtde_control.moveL(turn_U, 0.5, 0.3);
    rtde_control.moveL(upwards, 0.5, 0.3);
    
}

void FromVectorToRobot::MoveU2(){
        
    move_to_work_start();
    move_grip_point();
    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 3.14};
    std::vector<double> move_up_10 = {0, 0, -0.1, 0, 0, 3.14};

    // Pose transformations
    std::vector<double> turn_U = PT.pose_trans(correct_grip_point, ninety_deg_z);
    std::vector<double> upwards = PT.pose_trans(correct_grip_point, move_up_10);

    // Move commands
    rtde_control.moveL(turn_U, 0.5, 0.3);
    rtde_control.moveL(upwards, 0.5, 0.3);
}

void FromVectorToRobot::MoveD(){

}

void FromVectorToRobot::MoveDPrime(){

}

void FromVectorToRobot::MoveD2(){

}

void FromVectorToRobot::MoveR(){

}

void FromVectorToRobot::MoveRPrime(){

}

void FromVectorToRobot::MoveR2(){

}

void FromVectorToRobot::MoveL(){

}

void FromVectorToRobot::MoveLPrime(){

}

void FromVectorToRobot::MoveL2(){

}

void FromVectorToRobot::MoveF(){

}

void FromVectorToRobot::MoveFPrime(){

}

void FromVectorToRobot::MoveF2(){

}

void FromVectorToRobot::MoveB(){

}

void FromVectorToRobot::MoveBPrime(){

}

void FromVectorToRobot::MoveB2(){

}

int main(){
    FromVectorToRobot move;
    move.MoveU();
    std::cout << "MoveU finished" << std::endl;
    move.MoveUPrime();

}