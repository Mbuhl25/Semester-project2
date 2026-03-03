// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

int main() {
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");
std::vector<double> joint_positions = rtde_receive.getActualQ();
}
