#ifndef FROMVECTOROROBOT_H
#define FROMVECTOROROBOT_H

#include <vector>
#include <string>
#include "Algorithm.h"

class FromVectorToRobot {

public:
    FromVectorToRobot() {}
    std::string VecMove(std::vector<std::string> moves);

    void MoveU();

    void MoveUPrime();

    void MoveU2();

    void MoveD();

    void MoveDPrime();

    void MoveD2();

    void MoveR();

    void MoveRPrime();

    void MoveR2();

    void MoveL();

    void MoveLPrime();

    void MoveL2();

    void MoveF();

    void MoveFPrime();

    void MoveF2();

    void MoveB();

    void MoveBPrime();

    void MoveB2();

private:

};

#endif