#include "FromVectorToRobot.h"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
//#include "Algorithm.h"
#include <iostream>
#include <sstream>

//Algorithm alg;

//std::string FromVectorToRobot::VecMove(std::vector<std::string> moves){}

std::vector<double> working_frame = {0.107044, -0.381108, 0.1755723, -2.14, -1.57, 0};

void move_to_work_start(){

ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

rtde_control.moveJ({1.95257, -1.69021, 2.28666, -2.14271, -1.57025, 0}, 0.5, 0.3);

}


void FromVectorToRobot::MoveU(){
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

rtde_control.moveL(working_frame, 0.5, 0.3);
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
    
    move.MoveU();
    move_to_work_start();
}