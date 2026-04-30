// Include the correct header for the control interface:
#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>
#include <iostream>
#include <string.h>
#include <Eigen/Dense>


// Helper functions(makes sure that we can use the name of the poses)
ur_rtde::PathEntry makeMoveL_TCP(const std::vector<double>& pose, double speed, double acceleration, double blend)
{
    return ur_rtde::PathEntry{
        ur_rtde::PathEntry::MoveL,
        ur_rtde::PathEntry::PositionTcpPose,
        {
            pose[0], pose[1], pose[2],
            pose[3], pose[4], pose[5],
            speed, acceleration, blend
        }
    };
}

ur_rtde::PathEntry makeMoveJ_TCP(const std::vector<double>& pose, double speed, double acceleration, double blend)
{
    return ur_rtde::PathEntry{
        ur_rtde::PathEntry::MoveJ,
        ur_rtde::PathEntry::PositionTcpPose,
        {
            pose[0], pose[1], pose[2],
            pose[3], pose[4], pose[5],
            speed, acceleration, blend
        }
    };
}

ur_rtde::PathEntry makeMoveJ_Q(const std::vector<double>& pose, double speed, double acceleration, double blend)
{
    return ur_rtde::PathEntry{
        ur_rtde::PathEntry::MoveJ,
        ur_rtde::PathEntry::PositionJoints,
        {
            pose[0], pose[1], pose[2],
            pose[3], pose[4], pose[5],
            speed, acceleration, blend
        }
    };
}

// Creates 3x3 Rotation matrix, the input is the data type -> Eigen::Vector3d with the rx ry rz values of the feature_pose
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
std::vector<double> pose_trans(const std::vector<double>& a, const std::vector<double>& b)
{
    Eigen::Matrix4d T1 = poseToMatrix(a);
    Eigen::Matrix4d T2 = poseToMatrix(b);

    Eigen::Matrix4d T = T1 * T2;

    return matrixToPose(T);
}


void move_to_work_start(){
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
    rtde_control.moveJ({1.95257, -1.69021, 2.28666, -2.14271, -1.57025, 1.57045}, 0.5, 0.3);
}


//also works now
void ain() {
    // Control robot
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
    
    // The robot has a 30 degree offset
    std::vector<double> base_correction = {0, 0, 0, 0, 0, 0.5236};
    std::vector<double> xyz_frame = {0.227425, -0.283882, 0.179427, -1.77164, -2.5876, -0.0029743};
    std::vector<double> corrected_xyz_frame = pose_trans(xyz_frame, base_correction);
    std::vector<double> work_start = {1.95257, -1.69021, 2.28666, -2.14271, -1.57025, 1.57045};
    std::vector<double> cube_approach_point = {0.000942241, -0.38335, 0.15344488, -1.74705, -2.58713, -0.0208294};



    std::vector<double> grip_point = {0.288383, -0.421722, 0.0409269, 3.04921, 0.717766, 0.10912};
    std::vector<double> move_up_10_cm = {0, 0, 0.1, 0, 0, 0};

    ur_rtde::Path path;

    double speed = 0.2;
    double acceleration = 0.1;
    double blend = 0.05;

    path.addEntry(makeMoveL_TCP(xyz_frame, speed, acceleration, blend));
    path.addEntry(makeMoveL_TCP(cube_approach_point, speed, acceleration, blend));

    rtde_control.moveL(xyz_frame, speed, acceleration);

    

}

int main(){
    // Control robot
    ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");

    double speed = 0.2;
    double acceleration = 0.1;
    double blend = 0.05;


    // Correct base xyz joint positions {-1.17831, -1.57082, -1.5708, -1.57075, 1.57065, 0}
    std::vector<double> correct_base_xyz = {0.082022, -0.493722, 0.263118, 0.607995, -3.07307, 0.00410005};
    std::vector<double> cube_grip_point = {0.096295, -0.499677, 0.0416933, 0.603629, -3.07408, 0.00411514};
    std::vector<double> cube_approach_point = {0.0953148, -0.499014, 0.0861533, 0.60373, -3.07406, 0.00417964};
    std::vector<double> up_10 = {0, 0, -0.1, 0, 0, 0};
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 1.57};
    std::vector<double> minus_ninety_deg_z = {0, 0, 0, 0, 0, -1.57};
    std::vector<double> turn_U = pose_trans(cube_grip_point, ninety_deg_z);
    std::vector<double> turn_U_reverse = pose_trans(cube_grip_point, minus_ninety_deg_z);
    std::vector<double> move_up_10_cm = {0.0953148, -0.499014, 0.1861533, 0.60373, -3.07406, 0.00417964};
    std::vector<double> test = pose_trans(cube_grip_point, up_10);



    rtde_control.moveL(cube_approach_point, speed, acceleration);
    rtde_control.moveL(cube_grip_point, speed, acceleration);
    rtde_control.moveL(turn_U, speed, acceleration);
    rtde_control.moveL(move_up_10_cm, 0.1, acceleration);
    rtde_control.moveL(correct_base_xyz, 0.1, acceleration);
    rtde_control.moveL(cube_grip_point, 0.1, acceleration);
    rtde_control.moveL(turn_U_reverse, 0.1, acceleration);

    
}