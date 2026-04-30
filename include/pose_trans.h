#ifndef POSE_TRANS_H
#define POSE_TRANS_H
// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <string.h>
#include <Eigen/Dense>

class Pose_Trans {

public:
    Pose_Trans() {}

    ur_rtde::PathEntry makeMoveL_TCP(const std::vector<double>& pose, double speed, double acceleration, double blend);
    ur_rtde::PathEntry makeMoveJ_TCP(const std::vector<double>& pose, double speed, double acceleration, double blend);
    ur_rtde::PathEntry makeMoveJ_Q(const std::vector<double>& pose, double speed, double acceleration, double blend);

    Eigen::Matrix3d rodrigues(const Eigen::Vector3d& r);
    Eigen::Matrix4d poseToMatrix(const std::vector<double>& p);
    std::vector<double> matrixToPose(const Eigen::Matrix4d& T);
    std::vector<double> pose_trans(const std::vector<double>& a, const std::vector<double>& b);
    void move_to_work_start();

};

#endif