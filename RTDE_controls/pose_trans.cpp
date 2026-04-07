// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <string.h>
#include <Eigen/Dense>


// Creates 3x3 Rotation matrix, input is data type -> Eigen::Vector3d with the rx ry rz values of the feature_pose
Eigen::Matrix3d rodrigues(const Eigen::Vector3d& r)
{
    double theta = r.norm();
    if (theta < 1e-9)
        return Eigen::Matrix3d::Identity();

    Eigen::Vector3d u = r / theta;

    Eigen::Matrix3d K;
    K <<     0,   -u.z(),  u.y(),
          u.z(),      0,  -u.x(),
         -u.y(),   u.x(),     0;

    Eigen::Matrix3d I = Eigen::Matrix3d::Identity();

    return I * std::cos(theta)
         + (1 - std::cos(theta)) * (u * u.transpose())
         + K * std::sin(theta);
}


// Creates the 4x4 Transformation matrix
Eigen::Matrix4d poseToMatrix(const std::vector<double>& p)
{
    Eigen::Matrix4d T = Eigen::Matrix4d::Identity();

    // translation
    T(0,3) = p[0];
    T(1,3) = p[1];
    T(2,3) = p[2];

    // rotation
    Eigen::Vector3d r(p[3], p[4], p[5]);
    Eigen::Matrix3d R = rodrigues(r);

    T.block<3,3>(0,0) = R;

    return T;
}

// Reverts the transformation matrix from 4x4 back to 3x3
std::vector<double> matrixToPose(const Eigen::Matrix4d& T)
{
    std::vector<double> p(6);

    // translation
    p[0] = T(0,3);
    p[1] = T(1,3);
    p[2] = T(2,3);

    // rotation
    Eigen::Matrix3d R = T.block<3,3>(0,0);

    double theta = std::acos((R.trace() - 1.0) / 2.0);

    if (theta < 1e-9) {
        p[3] = p[4] = p[5] = 0.0;
        return p;
    }

    Eigen::Vector3d u;
    u << R(2,1) - R(1,2),
         R(0,2) - R(2,0),
         R(1,0) - R(0,1);

    u /= (2 * std::sin(theta));

    // rotation vector = axis * angle
    p[3] = u(0) * theta;
    p[4] = u(1) * theta;
    p[5] = u(2) * theta;

    return p;
}


// The finished pose_trans function where the inputs are the reference frame(a) and the offeset pose(b)(the transform relative to a)
std::vector<double> pose_trans(const std::vector<double>& a,
                               const std::vector<double>& b)
{
    Eigen::Matrix4d T1 = poseToMatrix(a);
    Eigen::Matrix4d T2 = poseToMatrix(b);

    Eigen::Matrix4d T = T1 * T2;

    return matrixToPose(T);
}



int main() {
    // Control robot
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
    
    // The robot has a 30 degree offset
    std::vector<double> base_correction = {0, 0, 0, 0, 0, 0.5236};
    std::vector<double> ref_frame = {0.151702, -0.319567, 0.136781, -1.10679, -2.88093, 0.0202264};
    std::vector<double> corrected_ref_frame = pose_trans(ref_frame, base_correction);


    std::vector<double> move_forward_20_cm = {-0, 0, 0, 0, 0, 0};

    std::vector<double> rubiks_cube = pose_trans(corrected_ref_frame, move_forward_20_cm);

    rtde_control.moveL(rubiks_cube, 0.5 , 0.3);

}