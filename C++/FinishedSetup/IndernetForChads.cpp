#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>

const std::string ESP32_IP = "10.167.228.102";
const int PORT = 8080;

class GripperConnection {
private:
    int sock = -1;

public:
    bool connect_to_esp32() {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;

        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        inet_pton(AF_INET, ESP32_IP.c_str(), &server.sin_addr);

        if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
            std::cerr << "Connection failed" << std::endl;
            close(sock);
            sock = -1;
            return false;
        }

        std::cout << "Connected to ESP32" << std::endl;
        return true;
    }

    bool sendCommand(const std::string& command) {
        if (sock < 0) {
            if (!connect_to_esp32()) return false;
        }

        // Just send plain text with newline
        std::string msg = command + "\n";
        if (send(sock, msg.c_str(), msg.size(), 0) < 0) {
            std::cerr << "Send failed, reconnecting..." << std::endl;
            close(sock);
            sock = -1;
            if (!connect_to_esp32()) return false;
            send(sock, msg.c_str(), msg.size(), 0);
        }

        // Read response
        char buffer[64];
        memset(buffer, 0, sizeof(buffer));
        recv(sock, buffer, sizeof(buffer), 0);
        std::cout << "Response: " << buffer;

        return true;
    }

    void gripperOpen()  { sendCommand("open"); }
    void gripperClose() { sendCommand("close"); }

    ~GripperConnection() {
        if (sock >= 0) close(sock);
    }
};

int main() {
    GripperConnection gripper;

    if (!gripper.connect_to_esp32()) {
        std::cerr << "Failed to connect" << std::endl;
        return 1;
    }

    while (true) {
        gripper.gripperOpen();
        
        gripper.gripperClose();
    }

    return 0;
}