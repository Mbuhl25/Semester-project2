#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

#include <iostream>
#include <thread>

using namespace ur_rtde;

int main()
{
    // Change this to your robot or URSim IP
    std::string robot_ip = "192.168.1.11";

    RTDEControlInterface rtde_control(robot_ip);
    RTDEReceiveInterface rtde_receive(robot_ip);

    // -----------------------------
    // 1. Move to a known start pose
    // -----------------------------
    std::vector<double> start_pose = {
        -0.4, -0.3, 0.3,   // x, y, z (meters)
         0.0, 3.14, 0.0    // rx, ry, rz
    };

    std::cout << "Moving to start pose..." << std::endl;
    rtde_control.moveL(start_pose, 0.3, 0.5);

    // -----------------------------
    // 2. Build a path
    // -----------------------------
    ur_rtde::Path path;

    double speed = 0.1;        // m/s
    double acceleration = 0.1;  // m/s^2
    double blend = 0.05;        // meters

    // Rectangle in XY plane
    path.addEntry({
        PathEntry::MoveL,
        PathEntry::PositionTcpPose,
        {-0.4, -0.3, 0.3, 0.0, 0, 0.0, speed, acceleration, blend}
    });

    path.addEntry({
        PathEntry::MoveL,
        PathEntry::PositionTcpPose,
        { -0.4, -0.5, 0.3, 0.0, 1.57, 0.0, speed, acceleration, blend }
    });

    path.addEntry({
        PathEntry::MoveL,
        PathEntry::PositionTcpPose,
        { -0.6, -0.5, 0.3, 0.0, 3.14, 0.0, speed, acceleration, blend }
    });

    path.addEntry({
        PathEntry::MoveL,
        PathEntry::PositionTcpPose,
        { -0.6, -0.3, 0.1, 0.0, -1.57, 0.0, speed, acceleration, 0 } // last blend MUST be 0
    });

    // -----------------------------
    // 3. Execute path (blocking)
    // -----------------------------
    std::cout << "Executing movePath..." << std::endl;
    rtde_control.movePath(path, false);

    std::cout << "Path completed!" << std::endl;

    return 0;
}
