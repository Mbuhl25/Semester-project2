#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "Mathias Bergholt - iPhone (2)";
const char* password = "Mathias8";

WiFiUDP udp;
const int UDP_PORT = 8080;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

class Gripper {
public:
    void begin() {
        Wire.begin();
        pwm.begin();
        pwm.setPWMFreq(50);
        pwm.setPWM(0, 0, 150);
    }
    void open()  { pwm.setPWM(0, 0, 350); }
    void close() { pwm.setPWM(0, 0, 245); }
};

Gripper gripper;

void ensureWiFi() {
    if (WiFi.status() == WL_CONNECTED) return;
    Serial.println("WiFi lost, reconnecting...");
    WiFi.disconnect();
    WiFi.begin(ssid, password);
    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries++ < 20) {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED)
        Serial.println("\nWiFi reconnected");
}

void setup() {
    Serial.begin(115200);
    delay(2000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);  // no static IP, just DHCP

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected!");
    Serial.println(WiFi.localIP());  // print whatever IP it got

    gripper.begin();
    udp.begin(UDP_PORT);
    Serial.println("UDP listening on port 8080");
}
int lastSeq = -1;

void loop() {
    ensureWiFi();

    int packetSize = udp.parsePacket();
    if (packetSize) {
        char buffer[64] = {};
        udp.read(buffer, sizeof(buffer) - 1);
        String msg = String(buffer);
        msg.trim();

        // Parse "seq:command"
        int colonIndex = msg.indexOf(':');
        if (colonIndex == -1) return;  // malformed

        int seq = msg.substring(0, colonIndex).toInt();
        String command = msg.substring(colonIndex + 1);

        Serial.println("Seq: " + String(seq) + " Command: " + command);

        // Always reply, but only move servo if new command
        String response = "unknown command";

        if (command == "open") {
            if (seq != lastSeq) {
                gripper.open();
                delay(500);
          }
          response = String(seq) + ":opened";
}       else if (command == "close") {
            if (seq != lastSeq) {
                gripper.close();
                delay(500);
    }
    response = String(seq) + ":closed";
}

        lastSeq = seq;

        udp.beginPacket(udp.remoteIP(), 8081);
        udp.print(response);
        udp.endPacket();
    }

    delay(5);
}