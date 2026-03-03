from rtde_receive import RTDEReceiveInterface

ROBOT_IP = "192.168.1.11"
rtde_r = RTDEReceiveInterface(ROBOT_IP)

print(dir(rtde_r))

print("Robot model:", rtde_r.getRobotModel())
print("TCP pose   :", rtde_r.getActualTCPPose())
print("Q actual   :", rtde_r.getActualQ())

rtde_r.disconnect()