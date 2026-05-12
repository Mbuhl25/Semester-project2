#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>

const char* ssid     = "OnePlus Nord 5 d3ti";
const char* password = "gtxa8399";

WiFiServer tcpServer(8080);  // Raw TCP on port 8080
WiFiClient client;           // Persistent client connection

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

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  gripper.begin();
  tcpServer.begin();
  Serial.println("TCP Server started on port 8080");
}

void loop() {
  // Accept new client if none connected
  if (!client || !client.connected()) {
    client = tcpServer.accept();
    if (client) {
      Serial.println("Client connected");
    }
  }

  // Read command if client is connected
  if (client && client.connected() && client.available()) {
    String command = client.readStringUntil('\n');
    command.trim();  // Remove whitespace/newline

    Serial.println("Command: " + command);

    if (command == "open") {
      gripper.open();
      client.println("opened");
    } 
    else if (command == "close") {
      gripper.close();
      client.println("closed");
    }
    else {
      client.println("unknown command");
    }
  }
}