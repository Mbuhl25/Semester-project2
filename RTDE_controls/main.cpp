// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>

int main() {
// Get current position
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");
std::vector<double> joint_positions = rtde_receive.getActualQ();

for (double q : joint_positions) {
    std::cout << q << ", ";
}


// move robot to position
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
rtde_control.moveL({0.540398, -1.07038, -0.0211795, 5.34891, 0.00659544, -0.650891}, 0.5, 0.2);

}
