#include "FromVectorToRobot.h"
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include "Algorithm.h"
#include <iostream>
#include <sstream>

Algorithm alg;

std::string FromVectorToRobot::VecMove(std::vector<std::string> moves){
    alg.moves = moves;
    std::string output = alg.switchpoints();

    std::istringstream iss(output);
    std::string move;
    while (iss >> move) {
        if      (move == "U")   { }
        else if (move == "U'")  { }
        else if (move == "2U")  { }
        else if (move == "D")   { }
        else if (move == "D'")  { }
        else if (move == "2D")  { }
        else if (move == "R")   { }
        else if (move == "R'")  { }
        else if (move == "2R")  { }
        else if (move == "L")   { }
        else if (move == "L'")  { }
        else if (move == "2L")  { }
        else if (move == "F")   { }
        else if (move == "F'")  { }
        else if (move == "2F")  { }
        else if (move == "B")   { }
        else if (move == "B'")  { }
        else if (move == "2B")  { }
    }

    return output;
}
