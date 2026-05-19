#include <iostream>
#include <vector>
#include <string>

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

// #include "IndernetForChads.h"
#include "ManipolationOfRing.h"
#include "FromVectorToRobot.h"
#include "Color_Detection.h"


int main() {
    // GripperConnection gripper;
    Algorithm algorithmProcessor;
    Color_Detection cube_object("Lucas", 3);
    FromVectorToRobot robotMoves;

    std::cout << "Number 1" << std::endl;

    cv::namedWindow("Frame", cv::WINDOW_NORMAL);
    std::cout << "Number 2" << std::endl;
    cv::resizeWindow("Frame", 640, 480);
    std::cout << "Number 3" << std::endl;

    // BEVÆG GRIPPEREN NED TIL TERNINGEN
    // BEVÆG GRIPPEREN OP TIL KASSEN MED GUL SIDE ØVERST og blå side udad
    
    std::string sideY = cube_object.scan_one_side("Y");

    // Flyt tilbage
    // BEVÆG GRIPPEREN OP TIL KASSEN MED ORANGE SIDE ØVERST

    std::string sideO = cube_object.scan_one_side("O");

    // BEVÆG GRIPPEREN OP TIL KASSEN MED GRØN SIDE ØVERST

    std::string sideG = cube_object.scan_one_side("G");

    // BEVÆG GRIPPEREN OP TIL KASSEN MED HVID SIDE ØVERST

    std::string sideW = cube_object.scan_one_side("W");

    // BEVÆG GRIPPEREN OP TIL KASSEN MED RØD SIDE ØVERST

    std::string sideR = cube_object.scan_one_side("R");

    // BEVÆG GRIPPEREN OP TIL KASSEN MED BLÅ SIDE ØVERST

    std::string sideB = cube_object.scan_one_side("B");

    std::string cubeColorPlacements = sideY + sideO + sideG + sideW + sideR + sideB; // get the string for the positions of the cube, a solved cube has this string: "YYYYYYYYYOOOOOOOOOGGGGGGGGGWWWWWWWWWRRRRRRRRRBBBBBBBBB"
    

    min2phase::init();  // use min2phase to generate the solution for the rubix's cube
    std::string algorithmToSolve = min2phase::solve(cubeColorPlacements, 21, 1000000, 0, min2phase::APPEND_LENGTH | min2phase::USE_SEPARATOR, nullptr);
    std::cout << "This is the algorithm to solve the cube: \n" << algorithmToSolve << std::endl;

    std::vector<std::string> algorithmToSolveVector = algorithmProcessor.FromStringToVec(algorithmToSolve);     // use the algorithm class to get the solution algorithm as a vector instead of a strin
    std::string algorithmToSolveInBox = algorithmProcessor.switchpoints(algorithmToSolveVector);
    std::cout << "This is the algorithm to solve the cube while it is sitting in the box: \n" << algorithmToSolveInBox << std::endl;
    std::vector<std::string> algorithmToSolveInBoxVector = algorithmProcessor.FromStringToVec(algorithmToSolveInBox);

    for (int i = 0; i < algorithmToSolveInBoxVector.size(); ++i) {
        std::string move = algorithmToSolveInBoxVector[i];

        if (move[0] == '(' || move[0] == '.') {
            continue;
        }

        std::cout << "now time to move: " << move << std::endl;

        if      (move == "U")   {robotMoves.MoveU();}
        else if (move == "U'")  {robotMoves.MoveUPrime();}
        else if (move == "U2")  {robotMoves.MoveU(); robotMoves.MoveU();}
        else if (move == "D")   {robotMoves.MoveD();}
        else if (move == "D'")  {robotMoves.MoveDPrime();}
        else if (move == "D2")  {robotMoves.MoveD(); robotMoves.MoveD();}
        else if (move == "R")   {robotMoves.MoveR();}
        else if (move == "R'")  {robotMoves.MoveRPrime();}
        else if (move == "R2")  {robotMoves.MoveR(); robotMoves.MoveR();}
        else if (move == "L")   {robotMoves.MoveL();}
        else if (move == "L'")  {robotMoves.MoveLPrime();}
        else if (move == "L2")  {robotMoves.MoveL(); robotMoves.MoveL();}
        else if (move == "F")   {robotMoves.MoveF();}
        else if (move == "F'")  {robotMoves.MoveFPrime();}
        else if (move == "F2")  {robotMoves.MoveF(); robotMoves.MoveF();}
        else if (move == "B")   {robotMoves.MoveB();}
        else if (move == "B'")  {robotMoves.MoveBPrime();}
        else if (move == "B2")  {robotMoves.MoveB(); robotMoves.MoveB();}
    }
}
