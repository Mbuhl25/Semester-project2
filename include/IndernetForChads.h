#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <cstring>

inline const std::string SERIAL_PORT = "/dev/ttyUSB0"; // or /dev/ttyACM0 on Linux, /dev/cu.usbserial-* on Mac
inline const int BAUD_RATE = B115200;

class GripperConnection {
private:
    int fd = -1;

    bool openPort() {
        fd = open(SERIAL_PORT.c_str(), O_RDWR | O_NOCTTY);
        if (fd < 0) { std::cerr << "Failed to open " << SERIAL_PORT << std::endl; return false; }

        termios tty{};
        tcgetattr(fd, &tty);
        cfsetospeed(&tty, BAUD_RATE);
        cfsetispeed(&tty, BAUD_RATE);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit chars
        tty.c_cflag |= (CLOCAL | CREAD);             // enable reading
        tty.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS); // no parity, 1 stop bit, no flow control
        tty.c_lflag = 0;                              // raw mode
        tty.c_oflag = 0;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY | ICRNL);

        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 30; // 3 second read timeout

        tcsetattr(fd, TCSANOW, &tty);
        tcflush(fd, TCIOFLUSH);
        return true;
    }

    std::string readLine() {
        std::string line;
        char c;
        while (read(fd, &c, 1) == 1) {
            if (c == '\n') return line;
            if (c != '\r') line += c;
        }
        return ""; // timeout
    }

public:
    GripperConnection() { openPort(); }

    bool sendCommand(const std::string& command) {
        if (fd < 0 && !openPort()) return false;

        static int seq = 0;
        seq++;
        std::string msg = std::to_string(seq) + ":" + command + "\n";
        std::cout << "Sending: " << command << std::endl;

        for (int attempt = 0; attempt < 5; ++attempt) {
            write(fd, msg.c_str(), msg.size());

            std::string reply = readLine();
            if (reply.empty()) {
                std::cerr << "  attempt " << attempt + 1 << " timed out, retrying..." << std::endl;
                continue;
            }

            int colon = reply.find(':');
            if (colon == std::string::npos) { std::cerr << "  malformed response" << std::endl; continue; }

            int replySeq = std::stoi(reply.substr(0, colon));
            if (replySeq != seq) { attempt--; continue; } // stale, don't count

            std::cout << "Confirmed: " << reply.substr(colon + 1) << std::endl;
            return true;
        }

        std::cerr << "Command failed after 5 attempts" << std::endl;
        return false;
    }

    bool gripperOpen()  { return sendCommand("open"); }
    bool gripperClose() { return sendCommand("close"); }

    ~GripperConnection() { if (fd >= 0) close(fd); }
};