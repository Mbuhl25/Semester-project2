#ifndef GRIPPER_H
#define GRIPPER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

class GripperConnection {

private:

    const std::string ESP32_IP = "10.167.228.102";
    const int PORT = 8080;
    int sock = -1;

public:

    bool connect_to_esp32();
    bool sendCommand(const std::string& command);
    void gripperOpen();
    void gripperClose();

    ~GripperConnection();

};


#endif