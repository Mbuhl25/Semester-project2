#ifndef FROMVECTOROROBOT_H
#define FROMVECTOROROBOT_H

#include <vector>
#include <string>

class FromVectorToRobot {

public:
    FromVectorToRobot() {}

    void turnRingSides(std::vector<double>, bool, std::string);

    std::string VecMove(std::vector<std::string> moves);

    void MoveU();
    void MoveUPrime();

    void MoveD();
    void MoveDPrime();

    void MoveR();
    void MoveRPrime();

    void MoveL();
    void MoveLPrime();

    void MoveF();
    void MoveFPrime();

    void MoveB();
    void MoveBPrime();

private:
    double speed = 0.1;
    double acceleration = 0.1;
};

#endif