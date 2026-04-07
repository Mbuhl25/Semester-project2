#include <iostream>
#include "CV2ForCPP.hpp"
#include "Kociemba.hpp"
int main() {

    CV camera;
    camera.useCamera();

    Kociemba solver;
    solver.func();

    return 0;
}