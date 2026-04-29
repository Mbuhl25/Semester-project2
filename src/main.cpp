#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Algorithm.h"
#include "Color_Detection.h"

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

int main() {
    Algorithm algorithmProcessor;
    // Color_Detection cube_object("Lucas", 3);

    // // get the string for the positions of the cube, a solved cube has this string:
    // // with colors: "YYYYYYYYYOOOOOOOOOGGGGGGGGGWWWWWWWWWRRRRRRRRRBBBBBBBBB"
    // std::string cubeColorPlacements = cube_object.scan_whole_cube();
    // // with orientations: "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"
    // std::string cubeOrientationPlacements = cube_object.rename_colors_to_orientations(cubeColorPlacements);

    // use min2phase to generate the solution for the rubix's cube
    std::string cubeOrientationPlacements = "UUUUUUULURRRRRDRRRFFFBFFFBFDDDDDDDRDLLLULLLLLBBBFBFBBB";
    min2phase::init();
    std::string algorithmToSolve = min2phase::solve(cubeOrientationPlacements, 21, 1000000, 0, min2phase::APPEND_LENGTH | min2phase::USE_SEPARATOR, nullptr);
    std::cout << algorithmToSolve << std::endl;

    // use the algorithm class to get the solution algorithm as a vector instead of a string
    std::vector<std::string> algorithmToSolveVector = algorithmProcessor.FromStringToVec(algorithmToSolve);

    std::string output = algorithmProcessor.switchpoints(algorithmToSolveVector);
    
    std::cout << output << std::endl;

    // if      (move == "U")   { }
    // else if (move == "U'")  { }
    // else if (move == "2U")  { }
    // else if (move == "D")   { }
    // else if (move == "D'")  { }
    // else if (move == "2D")  { }
    // else if (move == "R")   { }
    // else if (move == "R'")  { }
    // else if (move == "2R")  { }
    // else if (move == "L")   { }
    // else if (move == "L'")  { }
    // else if (move == "2L")  { }
    // else if (move == "F")   { }
    // else if (move == "F'")  { }
    // else if (move == "2F")  { }
    // else if (move == "B")   { }
    // else if (move == "B'")  { }
    // else if (move == "2B")  { }
}
