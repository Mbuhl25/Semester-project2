#include "Gripper.h"

bool GripperConnection::connect_to_esp32() {
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

bool GripperConnection::sendCommand(const std::string& command) {
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

void GripperConnection::gripperOpen()  { sendCommand("open"); }
void GripperConnection::gripperClose() { sendCommand("close"); }

GripperConnection::~GripperConnection() {
    if (sock >= 0) close(sock);
}

