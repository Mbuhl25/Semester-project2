#include "Color_Detection.h"

int main(){
    Color_Detection cube_mathi("Mathi", 1);

    cube_mathi.print_side("Y");
    
    std::string whole_cube == cube_mathi.rename_colors_to_orientations(cube_mathi.scan_whole_cube());
}