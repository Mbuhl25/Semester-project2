#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Gripper class
class Gripper{
  public:
  
  //Constructer
  Gripper(){
    Wire.begin();
    Serial.begin(115200);
    pwm.begin();
    pwm.setPWM(0, 0 ,150);
    pwm.setPWMFreq(50);
  }
  //method for closeing gripper.
  void open(){
    pwm.setPWM(0, 0, 300);
  }
  // Method for opening gripper.
  void close(){
    pwm.setPWM(0, 0, 150);
  }
};