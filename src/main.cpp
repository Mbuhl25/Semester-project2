#include <iostream>
#include <vector>
#include <string>

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

#include "IndernetForChads.h"
#include "Algorithm.h"
#include "Color_Detection.h"

int main() {
    // Connect to robot
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
    std::vector<std::string> algorithmToSolveInBoxVector{"U", "U'", "R"};

    for (int i = 0; i < algorithmToSolveInBoxVector.size(); ++i) {
        std::string move = algorithmToSolveInBoxVector[i];

        if (move[0] == '(' || move[0] == '.') {
            continue;
        }

        std::cout << "now time to move: " << move << std::endl;

        if      (move == "U")   {robotMoveFunction_U()}
        else if (move == "U'")  {robotMoveFunction_Uprime()}
        else if (move == "U2")  {robotMoveFunction_U(); robotMoveFunction_U();}
        else if (move == "D")   {robotMoveFunction_D()}
        else if (move == "D'")  {robotMoveFunction_Dprime()}
        else if (move == "D2")  {robotMoveFunction_D(); robotMoveFunction_D()}
        else if (move == "R")   {robotMoveFunction_R()}
        else if (move == "R'")  {robotMoveFunction_Rprime()}
        else if (move == "R2")  {robotMoveFunction_R(); robotMoveFunction_R()}
        else if (move == "L")   {robotMoveFunction_L()}
        else if (move == "L'")  {robotMoveFunction_Lprime()}
        else if (move == "L2")  {robotMoveFunction_L(); robotMoveFunction_L()}
        else if (move == "F")   {robotMoveFunction_F()}
        else if (move == "F'")  {robotMoveFunction_Fprime()}
        else if (move == "F2")  {robotMoveFunction_F(); robotMoveFunction_F()}
        else if (move == "B")   {robotMoveFunction_B()}
        else if (move == "B'")  {robotMoveFunction_Bprime()}
        else if (move == "B2")  {robotMoveFunction_B(); robotMoveFunction_B()}
    }
}
