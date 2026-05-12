#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>
#include <thread>
#include <chrono>


inline const std::string ESP32_IP = "10.96.247.100";
inline const int PORT = 8080;

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
        std::string msg = command + "\n";
        if (send(sock, msg.c_str(), msg.size(), 0) < 0) {
            std::cerr << "Send failed, reconnecting..." << std::endl;
            close(sock);
            sock = -1;
            if (!connect_to_esp32()) return false;
            send(sock, msg.c_str(), msg.size(), 0);
        }
        // Wait briefly for response to arrive
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        char buffer[64];
        memset(buffer, 0, sizeof(buffer));
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);
        if (bytes > 0) {
            std::cout << "Response: " << buffer << std::endl;
        }
        return true;
    }

    void gripperOpen()  { sendCommand("open"); }
    void gripperClose() { sendCommand("close"); }

    ~GripperConnection() {
        if (sock >= 0) close(sock);
    }
};