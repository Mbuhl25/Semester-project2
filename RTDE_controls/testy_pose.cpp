// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <string.h>

int main() {
// Get current position
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");
std::vector<double> linear_positions_cup = rtde_receive.getActualTCPPose();

for (double q : linear_positions_cup) {
    std::cout << q << ", ";
}

// Home kordinater joint positions (7.19053e-05, -1.57076, -3.55879e-05, -1.57075, -3.60648e-05, -7.18276e-05)
// Svarer til (0, -90, 0 ,-90, 0, 0)

//control robot
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

std::vector<double> feature_pose = {0.225772, -0.394614, 0.10234, -1.17061, -2.88648, -0.0520045};
std::vector<double> move_to_ball = {0.1,-0.3, 0.2, 0, 0, 0};


std::string script = 
    "def my_prog():\n"
    "\tfeature_pose = p[0.225772, -0.394614, 0, -1.17061, -2.88648, -0.0520045]\n"
    "\tmove_to_ball = p[0.1,-0.1, 0.4, 0, 0, 0]\n"
    "\ttarget = pose_trans(move_to_ball, feature_pose)\n"
    "\tmovel(target)\n"
    "end\n"
    "my_prog()\n";

rtde_control.sendCustomScript(script);





}




