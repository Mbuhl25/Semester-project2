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
//rtde_control.moveL({-0.143, 0.435, 0.20, -0.001, 3.12, 0.04}, 0.5, 0.2);

//Sekvens hvor vi viser terningen til camera
//rtde_control.moveJ({1.97, -0.76, 0.24, -1.06, 1.55, 0}, 0.5, 0.3);
//rtde_control.moveJ({0, -1.57076, 0, -1.57075, 0, 0}, 0.5, 0.3);

//Base frame
rtde_control.moveJ({0.4, -1.56, 0, -1.56, 0, 0}, 0.5, 0.3);

}
