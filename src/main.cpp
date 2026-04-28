#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Algorithm.h"
#include "Color_Detection.h"

#include <min2phase/min2phase.h>
#include <min2phase/tools.h>

int main() {
    Color_Detection cube_mathi("Lucas", 3);
    Algorithm alg;
    min2phase::init(); //precomputed coordinates

    //cube_mathi.align_cube();

    std::string whole_cube = cube_mathi.rename_colors_to_orientations(cube_mathi.scan_whole_cube());
    std::string input = min2phase::solve(whole_cube, 21, 1000000, 0, min2phase::APPEND_LENGTH | min2phase::USE_SEPARATOR, nullptr);
    alg.moves = alg.FromStringToVec(input);

    std::string output = alg.switchpoints();
    std::cout << input << std::endl;
    std::cout << output << std::endl;
}
