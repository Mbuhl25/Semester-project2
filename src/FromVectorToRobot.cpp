#include "FromVectorToRobot.h"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include "Algorithm.h"
#include <iostream>
#include <sstream>

Algorithm alg;

std::string FromVectorToRobot::VecMove(std::vector<std::string> moves){}

void FromVectorToRobot::MoveU(){
}
void FromVectorToRobot::MoveUPrime(){

}
void FromVectorToRobot::MoveD(){
    
}
        // else if (move == "U'")  {robotMoveFunction_Uprime()}
        // else if (move == "U2")  {robotMoveFunction_U(); robotMoveFunction_U();}
        // else if (move == "D")   {robotMoveFunction_D()}
        // else if (move == "D'")  {robotMoveFunction_Dprime()}
        // else if (move == "D2")  {robotMoveFunction_D(); robotMoveFunction_D()}
        // else if (move == "R")   {robotMoveFunction_R()}
        // else if (move == "R'")  {robotMoveFunction_Rprime()}
        // else if (move == "R2")  {robotMoveFunction_R(); robotMoveFunction_R()}
        // else if (move == "L")   {robotMoveFunction_L()}
        // else if (move == "L'")  {robotMoveFunction_Lprime()}
        // else if (move == "L2")  {robotMoveFunction_L(); robotMoveFunction_L()}
        // else if (move == "F")   {robotMoveFunction_F()}
        // else if (move == "F'")  {robotMoveFunction_Fprime()}
        // else if (move == "F2")  {robotMoveFunction_F(); robotMoveFunction_F()}
        // else if (move == "B")   {robotMoveFunction_B()}
        // else if (move == "B'")  {robotMoveFunction_Bprime()}
        // else if (move == "B2")  {robotMoveFunction_B(); robotMoveFunction_B()}