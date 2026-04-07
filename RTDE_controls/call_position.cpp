// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <string.h>
#include <Eigen/Dense>

int main() {
// Get current position
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");
std::vector<double> linear_positions_cup = rtde_receive.getActualTCPPose();

for (double q : linear_positions_cup) {
    std::cout << q << ", ";
}
}