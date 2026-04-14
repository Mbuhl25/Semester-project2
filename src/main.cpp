#include <iostream>
#include "Algorithm.h"
#include <vector>
#include <string>
#include <sstream>

int main() {

    Algorithm alg;

    std::string input =
        "R D R";

    alg.moves = alg.FromStringToVec(input);

    std::string output = alg.switchpoints();
    std::cout << input << std::endl;
    std::cout << output << std::endl;

    return 0;
}