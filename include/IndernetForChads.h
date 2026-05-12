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
    std::string msg = command + "\n";

    // Try sending, with one reconnect attempt
    for (int attempt = 0; attempt < 2; ++attempt) {
        if (sock < 0 && !connect_to_esp32()) {
            std::cerr << "Could not connect" << std::endl;
            return false;
        }

        ssize_t sent = send(sock, msg.c_str(), msg.size(), 0);
        if (sent == (ssize_t)msg.size()) {
            break;  // success
        }

        std::cerr << "Send failed (attempt " << attempt + 1 << "), reconnecting..." << std::endl;
        close(sock);
        sock = -1;

        if (attempt == 1) {
            std::cerr << "Send failed after reconnect" << std::endl;
            return false;
        }
    }

    // Wait for response with a proper timeout using select()
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    struct timeval tv = {2, 0};  // 2 second timeout

    int ready = select(sock + 1, &readfds, NULL, NULL, &tv);
    if (ready <= 0) {
        std::cerr << "No response received (timeout or error)" << std::endl;
        // Don't close — command may still have been received
        return false;
    }

    char buffer[64];
    memset(buffer, 0, sizeof(buffer));
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0) {
        std::cerr << "Connection closed by ESP32" << std::endl;
        close(sock);
        sock = -1;
        return false;
    }

    std::cout << "Response: " << buffer;
    return true;
    }

    void gripperOpen()  { sendCommand("open"); }
    void gripperClose() { sendCommand("close"); }

    ~GripperConnection() {
        if (sock >= 0) close(sock);
    }
};