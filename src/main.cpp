#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

#include "FromVectorToRobot.h"
#include "IndernetForChads.h"
#include "ManipolationOfRing.h"
#include "Color_Detection.h"

int main() {
    
    std::vector<std::string> algorithmToSolveInBoxVector{"F"};

    FromVectorToRobot RC;

    for (int i = 0; i < algorithmToSolveInBoxVector.size(); ++i) {
        std::string move = algorithmToSolveInBoxVector[i];

        if (move[0] == '(' || move[0] == '.') {
            continue;
        }

        std::cout << "now time to move: " << move << std::endl;

        if      (move == "U")   {RC.MoveU();}
        else if (move == "U'")  {RC.MoveUPrime();}
        else if (move == "U2")  {RC.MoveU(); RC.MoveU();}
        else if (move == "D")   {RC.MoveD();}
        else if (move == "D'")  {RC.MoveDPrime();}
        else if (move == "D2")  {RC.MoveD(); RC.MoveD();}
        else if (move == "R")   {RC.MoveR();}
        else if (move == "R'")  {RC.MoveRPrime();}
        else if (move == "R2")  {RC.MoveR(); RC.MoveR();}
        else if (move == "L")   {RC.MoveL();}
        else if (move == "L'")  {RC.MoveLPrime();}
        else if (move == "L2")  {RC.MoveL(); RC.MoveL();}
        else if (move == "F")   {RC.MoveF();}
        else if (move == "F'")  {RC.MoveFPrime();}
        else if (move == "F2")  {RC.MoveF(); RC.MoveF();}
        else if (move == "B")   {RC.MoveB();}
        else if (move == "B'")  {RC.MoveBPrime();}
        else if (move == "B2")  {RC.MoveB(); RC.MoveB();}
    }
}