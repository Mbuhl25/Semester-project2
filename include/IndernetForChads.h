#include <fcntl.h> 
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
        std::cout << "Attempting to connect to " << ESP32_IP << ":" << PORT << std::endl;
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
        
        // Set non-blocking
        fcntl(sock, F_SETFL, O_NONBLOCK);
        
        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        inet_pton(AF_INET, ESP32_IP.c_str(), &server.sin_addr);
        
        connect(sock, (sockaddr*)&server, sizeof(server));
        
        // Wait up to 3 seconds for connection
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(sock, &fdset);
        struct timeval tv = {3, 0}; // 3 second timeout
        
        if (select(sock + 1, NULL, &fdset, NULL, &tv) == 1) {
            int so_error;
            socklen_t len = sizeof(so_error);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error == 0) {
                // Set back to blocking
                fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) & ~O_NONBLOCK);
                std::cout << "Connected to ESP32" << std::endl;
                return true;
        }
    }

    std::cerr << "Connection failed/timed out" << std::endl;
    close(sock);
    sock = -1;
    return false;
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