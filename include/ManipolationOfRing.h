
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

class Algorithm {
public:
    Algorithm();

    std::vector<std::string> FromStringToVec(const std::string& input);
    std::string switchpoints(std::vector<std::string>);

private:
    int ring[4]; // L F R B

    void rotateD();
    void rotateDPrime();
    
    char resolve(char face);
};

#endif