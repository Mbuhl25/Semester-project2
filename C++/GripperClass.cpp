// Class to be run in Arduino DOES NOT COMPILE IN VS CODE. 
// This is just for reference.
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

// Making gripper object
Gripper gripper;

void setup(){
  //Everything is already set up
}

void loop(){
  gripper.open();
  delay(1000);
  gripper.close();
  delay(1000);
}
