// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

int main() {
// The constructor simply takes the IP address of the Robot
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
// First argument is the pose 6d vector followed by speed and acceleration
rtde_control.moveL({0, -192.46, 602.02, 0, 2.222, -2.222}, 0.5, 0.2);
}
