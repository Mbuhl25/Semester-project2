#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>

inline const std::string ESP32_IP = "10.96.247.100";
inline const int PORT = 8080;

class GripperConnection {
private:
    int sock = -1;
    sockaddr_in server;

    bool createSocket() {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) return false;

        sockaddr_in local{};
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(8081);
        bind(sock, (sockaddr*)&local, sizeof(local));

        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(PORT);
        inet_pton(AF_INET, ESP32_IP.c_str(), &server.sin_addr);

        struct timeval tv = {0, 300000};
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
        return true;
    }

public:
    GripperConnection() {
        createSocket();
    }

    bool sendCommand(const std::string& command) {
        if (sock < 0 && !createSocket()) return false;

        static int seq = 0;
        seq++;
        std::string msg = std::to_string(seq) + ":" + command;

        std::cout << "Sending: " << command << std::endl;

        for (int attempt = 0; attempt < 10; ++attempt) {
            sendto(sock, msg.c_str(), msg.size(), 0,
                   (sockaddr*)&server, sizeof(server));

            char buffer[64] = {};
            ssize_t bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes < 0) {
                std::cerr << "  attempt " << attempt + 1 << " failed, retrying..." << std::endl;
                continue;
            }

            // Parse "seq:response"
            std::string reply(buffer);
            int colon = reply.find(':');
            if (colon == std::string::npos) {
                std::cerr << "  malformed response, retrying..." << std::endl;
                continue;
            }

            int replySeq = std::stoi(reply.substr(0, colon));
            std::string replyMsg = reply.substr(colon + 1);

            if (replySeq != seq) {
                attempt--;  // don't count stale responses as attempts
                continue;
            }

            std::cout << "Confirmed: " << replyMsg << std::endl;
            return true;
        }

        std::cerr << "Command failed after 10 attempts" << std::endl;
        return false;
    }

    bool gripperOpen()  { return sendCommand("open"); }
    bool gripperClose() { return sendCommand("close"); }

    ~GripperConnection() {
        if (sock >= 0) close(sock);
    }
};