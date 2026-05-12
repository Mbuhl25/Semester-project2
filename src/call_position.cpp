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


// first position
// 0.225622, -0.28317, -0.028439, 3.081, 0.583755, -0.0933979

// second position

// -0.00514456, -0.378389, -0.0284158, -3.0639, -0.577202, 0.0293351