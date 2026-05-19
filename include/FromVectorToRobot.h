#ifndef FROMVECTOROROBOT_H
#define FROMVECTOROROBOT_H

#include <vector>
#include <string>

class FromVectorToRobot {

public:
    FromVectorToRobot() {}

    void turnRingSides(std::vector<double>, bool, std::string);

    std::string VecMove(std::vector<std::string> moves);
    void getPosition();
    void testFunction();

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
    double speed = 1;
    double acceleration = 1;
};

#endif