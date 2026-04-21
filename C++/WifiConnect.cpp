#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

const std::string ESP32_IP = "10.167.228.102"; // your ESP32's IP

bool sendGripperCommand(const std::string& command) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    inet_pton(AF_INET, ESP32_IP.c_str(), &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }

    std::string request = "GET /" + command + " HTTP/1.1\r\nHost: " + ESP32_IP + "\r\nConnection: close\r\n\r\n";
    send(sock, request.c_str(), request.size(), 0);

    char buffer[512];
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Gripper: " << command << std::endl;

    closesocket(sock);
    WSACleanup();
    return true;
}

void gripperOpen()  { sendGripperCommand("open"); }
void gripperClose() { sendGripperCommand("close"); }

int main() {
    while (true){
        gripperOpen();
        Sleep(2000);   // wait 2 seconds
        gripperClose();
        Sleep(2000);   // wait 2 seconds
    }
    return 0;
}