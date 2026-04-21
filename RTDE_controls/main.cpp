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

// Home kordinater (7.19053e-05, -1.57076, -3.55879e-05, -1.57075, -3.60648e-05, -7.18276e-05)
// Svarer til (0, -90, 0 ,-90, 0, 0)

//move robot to position
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
rtde_control.moveJ({0.540398, -1.07038, -0.0211795, 5.34891, 0.00659544, -0.650891}, 0.5, 0.2);

}
