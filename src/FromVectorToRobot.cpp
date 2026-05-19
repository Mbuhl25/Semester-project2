
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include <ur_rtde/rtde_control_interface.h>
#include <ur_rtde/rtde_receive_interface.h>

#include "FromVectorToRobot.h"
#include "KinematicsMath.h"
// #include "IndernetForChads.h" 

// GripperConnection gripper;
Kinematics PT;
// Connect to robot
ur_rtde::RTDEControlInterface rtde_control("192.168.1.11");
ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");

// Global waypoints
std::vector<double> parrallel_to_work_start = {-4.34557, -1.88197, 2.12536, -1.8126, -1.57616, -0.0307754}; // joint angles
std::vector<double> perpendicular_to_work_start = {-4.32317, -1.85988, 2.11749, -1.80833, -1.59106, 1.53886}; // joint angles
std::vector<double> parrallel_correct_grip_point = {0.224218, -0.283284, 0.0422329, 0.620214, -3.07384, 0}; // pose
std::vector<double> perpendicular_correct_grip_point = {0.225974, -0.281095, 0.0379604, -1.69162, -2.61414, 0.00921666}; // pose

// Helper functions
void move_parrallel_to_work_start(){
    rtde_control.moveJ(parrallel_to_work_start, 0.5, 0.3);
}

void move_perpendicular_to_work_start(){
    rtde_control.moveJ(perpendicular_to_work_start, 0.5, 0.3);
}

void move_parrallel_grip_point(){
    rtde_control.moveL(parrallel_correct_grip_point, 0.5, 0.3);
}

void move_perpendicular_grip_point() {
    rtde_control.moveL(perpendicular_correct_grip_point, 0.5, 0.3);
}


void FromVectorToRobot::turnRingSides(std::vector<double> offset, bool downFirst, std::string face) {
    // Movements
    std::vector<double> ninety_deg_y = {0, 0, 0, 0, 1.57, 0};
    std::vector<double> back_10cm_z = {0, 0, -0.1, 0, 0, 0};
    std::vector<double> forward_10cm_z = {0, 0, 0.1, 0, 0, 0};
    std::vector<double> back_11cm_x = {-0.114, 0, 0, 0, 0, 0};


    // Pose Transformations
    std::vector<double> move_to_side;
    if (face == "F" || face == "B") {
        move_to_side = PT.pose_trans(parrallel_correct_grip_point, offset);
    } else if (face == "R" || face == "L") {
        move_to_side = PT.pose_trans(perpendicular_correct_grip_point, offset);
    } else {
        std::cout << "invalid face name" << std::endl;
        exit(1);
    }
    std::vector<double> move_to_side_away = PT.pose_trans(move_to_side, back_10cm_z);
    std::vector<double> move_to_side_away_90degree_y = PT.pose_trans(move_to_side_away, ninety_deg_y); // just a midway calculation
    std::vector<double> move_to_side_halfway = PT.pose_trans(move_to_side_away_90degree_y, back_10cm_z); // just a midway calculation
    std::vector<double> move_after_turn_away = PT.pose_trans(move_to_side_halfway , back_11cm_x);
    std::vector<double> move_after_turn = PT.pose_trans(move_after_turn_away, forward_10cm_z);


    // Move commands
    if (downFirst) {
        rtde_control.moveL(move_to_side_away, speed, acceleration);
        rtde_control.moveL(move_after_turn_away, speed, acceleration);
        rtde_control.moveL(move_after_turn, speed, acceleration);
        // gripper.gripperClose();
        rtde_control.moveL(move_to_side, speed, acceleration);
        // gripper.gripperOpen();
        rtde_control.moveL(move_to_side_away, speed, acceleration);
    } else {
        rtde_control.moveL(move_to_side_away, speed, acceleration);
        rtde_control.moveL(move_to_side, speed, acceleration);
        // gripper.gripperClose();
        rtde_control.moveL(move_after_turn, speed, acceleration);
        // gripper.gripperOpen();
        rtde_control.moveL(move_after_turn_away, speed, acceleration);
        rtde_control.moveL(move_to_side_away, speed, acceleration);
    }
}


// Manipulation functions
void FromVectorToRobot::MoveU(){
    // Back to reference Position
    move_parrallel_to_work_start();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, 1.57};
    std::vector<double> back_10cm_z = {0, 0, -0.1, 0, 0, 0};
    // Pose transformations
    std::vector<double> turn_U = PT.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> move_away = PT.pose_trans(turn_U, back_10cm_z);

    // Move commands
    // gripper.gripperClose();
    rtde_control.moveL(parrallel_correct_grip_point, speed, acceleration);
    rtde_control.moveL(turn_U, speed, acceleration);
    // gripper.gripperOpen();
    rtde_control.moveL(move_away, speed, acceleration);
}

void FromVectorToRobot::MoveUPrime(){
    // Back to reference Position
    move_parrallel_to_work_start();

    // Movements
    std::vector<double> ninety_deg_z = {0, 0, 0, 0, 0, -1.57};
    std::vector<double> back_10cm_z = {0, 0, -0.1, 0, 0, 0};
    // Pose transformations
    std::vector<double> turn_UPrime = PT.pose_trans(parrallel_correct_grip_point, ninety_deg_z);
    std::vector<double> move_away = PT.pose_trans(turn_UPrime, back_10cm_z);

    // Move commands
    // gripper.gripperClose();
    rtde_control.moveL(parrallel_correct_grip_point, speed, acceleration);
    rtde_control.moveL(turn_UPrime, speed, acceleration);
    // gripper.gripperOpen();
    rtde_control.moveL(move_away, speed, acceleration);
}

void FromVectorToRobot::MoveL(){
    // Back to reference Position
    move_perpendicular_to_work_start();

    std::vector<double> place_tcp_left = {0, -0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_left, false, "L");
}

void FromVectorToRobot::MoveLPrime(){
    // Back to reference Position
    move_perpendicular_to_work_start();

    std::vector<double> place_tcp_left = {0, -0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_left, true, "L");
}

void FromVectorToRobot::MoveR(){
    // Back to reference Position
    move_perpendicular_to_work_start();

    std::vector<double> place_tcp_right = {0, 0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_right, true, "R");
}

void FromVectorToRobot::MoveRPrime(){
    // Back to reference Position
    move_perpendicular_to_work_start();

    std::vector<double> place_tcp_right = {0, 0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_right, false, "R");
}


void FromVectorToRobot::MoveF(){
    // Back to reference Position
    move_parrallel_to_work_start();

    std::vector<double> place_tcp_front = {0, -0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_front, false, "F");
}

void FromVectorToRobot::MoveFPrime(){
    // Back to reference Position
    move_parrallel_to_work_start();

    std::vector<double> place_tcp_front = {0, -0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_front, true, "F");
}


void FromVectorToRobot::MoveBPrime(){
    // Back to reference Position
    move_parrallel_to_work_start();

    std::vector<double> place_tcp_front = {0, 0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_front, false, "B");
}

void FromVectorToRobot::MoveB(){
    // Back to reference Position
    move_parrallel_to_work_start();

    std::vector<double> place_tcp_front = {0, 0.02, 0, 0, 0, 0};
    turnRingSides(place_tcp_front, true, "B");
}


void FromVectorToRobot::MoveD(){
    // Movements
    std::vector<double> forward_2cm_z = {0, 0, 0.02, 0, 0, 0};
    std::vector<double> offset = {0, 0.02, 0, 0, 0, 0};
    std::vector<double> back_10cm_z = {0, 0, -0.1, 0, 0, 0};

    // Pose Transformations
    std::vector<double> move_to_side_R = PT.pose_trans(perpendicular_correct_grip_point, offset);
    std::vector<double> move_to_side_lower_R = PT.pose_trans(move_to_side_R, forward_2cm_z);
    std::vector<double> move_to_side_away_R = PT.pose_trans(move_to_side_R, back_10cm_z);

    std::vector<double> move_to_side_F = PT.pose_trans(parrallel_correct_grip_point, offset);
    std::vector<double> move_to_side_lower_F = PT.pose_trans(move_to_side_F, forward_2cm_z);
    std::vector<double> move_to_side_away_F = PT.pose_trans(move_to_side_F, back_10cm_z);


    // Move commands
    rtde_control.moveL(move_to_side_away_R, speed, acceleration);
    rtde_control.moveL(move_to_side_lower_R, speed, acceleration);
    // // gripper.gripperClose();
    rtde_control.moveL(move_to_side_R, speed, acceleration);
    rtde_control.moveL(move_to_side_F, speed, acceleration);
    // // gripper.gripperOpen();
    rtde_control.moveL(move_to_side_lower_F, speed, acceleration);
    rtde_control.moveL(move_to_side_away_F, speed, acceleration);
}

void FromVectorToRobot::MoveDPrime(){
    // Movements
    std::vector<double> forward_2cm_z = {0, 0, 0.02, 0, 0, 0};
    std::vector<double> offset = {0, 0.02, 0, 0, 0, 0};
    std::vector<double> back_10cm_z = {0, 0, -0.1, 0, 0, 0};

    // Pose Transformations
    std::vector<double> move_to_side_R = PT.pose_trans(perpendicular_correct_grip_point, offset);
    std::vector<double> move_to_side_lower_R = PT.pose_trans(move_to_side_R, forward_2cm_z);
    std::vector<double> move_to_side_away_R = PT.pose_trans(move_to_side_R, back_10cm_z);

    std::vector<double> move_to_side_F = PT.pose_trans(parrallel_correct_grip_point, offset);
    std::vector<double> move_to_side_lower_F = PT.pose_trans(move_to_side_F, forward_2cm_z);
    std::vector<double> move_to_side_away_F = PT.pose_trans(move_to_side_F, back_10cm_z);


    // Move commands
    rtde_control.moveL(move_to_side_away_F, speed, acceleration);
    rtde_control.moveL(move_to_side_lower_F, speed, acceleration);
    // // gripper.gripperClose();
    rtde_control.moveL(move_to_side_F, speed, acceleration);
    rtde_control.moveL(move_to_side_R, speed, acceleration);
    // // gripper.gripperOpen();
    rtde_control.moveL(move_to_side_lower_R, speed, acceleration);
    rtde_control.moveL(move_to_side_away_R, speed, acceleration);
}

void FromVectorToRobot::getPosition() {
    // Get current position
    ur_rtde::RTDEReceiveInterface rtde_receive("192.168.1.11");
    std::vector<double> linear_positions_cup = rtde_receive.getActualTCPPose();

    for (double q : linear_positions_cup) {
        std::cout << q << ", ";
    }
}

void FromVectorToRobot::testFunction() {
    std::vector<double> back_15cm_z = {0, 0, -0.15, 0, 0, 0};

    std::vector<double> cubeScanPoint = {-0.0740231, -0.707492, 0.530124, 0.0, 0.0, 0.430287}; // pose
    std::vector<double> cubeScanPoint_away = PT.pose_trans(cubeScanPoint, back_15cm_z); // pose

    rtde_control.moveL(cubeScanPoint_away, 0.1, 0.1);
    rtde_control.moveL(cubeScanPoint, 0.1, 0.1);
}
