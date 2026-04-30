#include <iostream>
#include <vector>
#include <string>

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

#include "Algorithm.h"
#include "Color_Detection.h"

int main() {
    Algorithm algorithmProcessor;
    Color_Detection cube_object("Lucas", 1);


    std::string cubeColorPlacements = "YYYYYYYYYGGGOOOOOORRRGGGGGGWWWWWWWWWBBBRRRRRROOOBBBBBB";                            // get the string for the positions of the cube, a solved cube has this string: "YYYYYYYYYOOOOOOOOOGGGGGGGGGWWWWWWWWWRRRRRRRRRBBBBBBBBB"
    
    std::string cubeOrientationPlacements = cube_object.rename_colors_to_orientations(cubeColorPlacements);     // and expressed as an orientations: "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB"

    
    min2phase::init();      // use min2phase to generate the solution for the rubix's cube
    std::string algorithmToSolve = min2phase::solve(cubeOrientationPlacements, 21, 1000000, 0, min2phase::APPEND_LENGTH | min2phase::USE_SEPARATOR, nullptr);
    std::cout << "This is the algorithm to solve the cube: \n" << algorithmToSolve << std::endl;

    
    std::vector<std::string> algorithmToSolveVector = algorithmProcessor.FromStringToVec(algorithmToSolve);     // use the algorithm class to get the solution algorithm as a vector instead of a string

    std::string algorithmToSolveInBox = algorithmProcessor.switchpoints(algorithmToSolveVector);
    std::cout << "This is the algorithm to solve the cube while it is sitting in the box: \n" << algorithmToSolveInBox << std::endl;



    std::vector<std::string> algorithmToSolveInBoxVector = algorithmProcessor.FromStringToVec(algorithmToSolveInBox);
    for (int i = 0; i < algorithmToSolveInBoxVector.size(); ++i) {
        std::string move = algorithmToSolveInBoxVector[i];

        if (algorithmToSolveInBoxVector[i] == ".") {
            continue;
        } else if (algorithmToSolveInBoxVector[i][0] == '(') {
            continue;
        }

        std::cout << "now time to move: " << move << std::endl;

        // if      (move == "U")   {robotMoveFunction_U()}
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
    }
}
