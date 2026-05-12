#include <iostream>
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

int main()
{

// X, Y Z, Rx, Ry, Rz
    std::vector<double> Position = {0.0, 0.0, 0.0, 0.0, 1.570, 0.0};

// I kordinater
    rtde_control.moveL(Position, 0.5, 0.5);

// I grader
    rtde_control.moveJ(Position, 0.5, 0.5);

    return 0;

}
