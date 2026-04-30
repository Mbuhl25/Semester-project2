#include "FromVectorToRobot.h"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
//#include "Algorithm.h"
#include "pose_trans.h"
#include <iostream>
#include <sstream>

//Algorithm alg;

//std::string FromVectorToRobot::VecMove(std::vector<std::string> moves){}

std::vector<double> grip_point = {0.22657, -0.285007, 0.0422215, 0.620214, -3.07384, 0};

void move_to_work_start(){

ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

rtde_control.moveL({0.210568, -0.283833, 0.130525, 0.552248, -3.07929, 0}, 0.5, 0.3);

}

void move_grip_point(){
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

    rtde_control.moveL(grip_point, 0.5, 0.3);
}

void FromVectorToRobot::MoveU(){
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

    move_grip_point();

}

void FromVectorToRobot::MoveUPrime(){

}

void FromVectorToRobot::MoveU2(){

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
    
    move_to_work_start();
}