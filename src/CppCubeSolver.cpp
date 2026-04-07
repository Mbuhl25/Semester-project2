#include <iostream>
#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

int main(int argc, char *argv[]){

    min2phase::init();//precomputed coordinates

    std::cout << min2phase::solve(min2phase::tools::randomCube(), 21, 1000000, 0, min2phase::APPEND_LENGTH | min2phase::USE_SEPARATOR, nullptr);
    return 0;
}