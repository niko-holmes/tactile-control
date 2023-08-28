#include "ServoBD.h"
#include "PID.h"
#include "TactileSensor.h"
#include <Wire.h>
#include "vector3.h"

//Servo
ServoBD servo(5, 6);

//PID Controller
PID pid(1, 0.1, 1);

//Sensors
TactileSensor finger1(0b0001100, 0b0001101, 0b0001110, 0b0001111);
TactileSensor finger2(0b0001100, 0b0001101, 0b0001110, 0b0001111);
TactileSensor finger3(0b0001100, 0b0001101, 0b0001110, 0b0001111);

double Fz_target = 10.00;     //Target Z force [N]
int sampling_time = 100;      //Sampling time [ms]

uint8_t duty_cycle_max = 255;
uint8_t duty_cycle_min = 100;

void setup(){
  pinMode(12, INPUT_PULLUP);  //Set PIN12 to input using the internal pull-up resistor. PIN10 for start/stop button
  pinMode(11, INPUT_PULLUP);  //Set PIN11 to input using the internal pull-up resistor. PIN11 for lower calibration button
  pinMode(10, INPUT_PULLUP);  //Set PIN10 to input using the internal pull-up resistor. PIN12 for upper calibration button
  Wire.begin();               //Initialize I2C connection
  Serial.begin(9600);         //Initialize serial monitor

  Serial.println("Waiting to start system...");
  while(digitalRead(12) == HIGH){
    //Pause until start button is pressed
  }
  Serial.println("STARTING SYSTEM");
  Serial.println();
}

void loop(){
  /*Main Control Loop.
  Read sensor data then calculate control output using PID controller.
  If control output is positive rotate servo forward, else rotate it backwards.
  If control output is 0, stop servo.

  Delay by sampling time T.

  :return: None
  */

  //If the button connected to pin 12 is pressed, the servo will be reset and the control loop will stop
  if(digitalRead(12) == LOW){ 
    Serial.println("STOPPING SYSTEM");
    Serial.println("Resetting Servo...");
    resetServo();
    Serial.println("Servo Reset");
    Serial.println("Press Arduino Reset button to restart system");
    return;
  }

  //Read sensor data and return vector of largest force in each axis
  vector3_double max_force = readSensors();

  //Calculate control output
  int ut = pid.calculate(Fz_target, max_force.z);  
  
  uint8_t duty_cycle = uint8_t((((abs(ut) - 0)*(duty_cycle_max - duty_cycle_min)) / (Fz_target - 0)) + duty_cycle_min); //Convert ut to duty cycle value range (100 to 255);

  //Rotate servo
  if(digitalRead(10) == LOW || digitalRead(11) == LOW || ut == 0){
    servo.off();
  }
  else if(ut > 0){ 
    servo.forward(duty_cycle);
  }
  else if(ut < 0){
    servo.backward(duty_cycle);
  }

  //Print force, u(t), and duty_cycle data
  Serial.print("xForce: ");
  Serial.println(max_force.x);
  Serial.print("yForce: ");
  Serial.println(max_force.y);
  Serial.print("zForce: ");
  Serial.println(max_force.z);
  Serial.print("u(t): ");
  Serial.println(ut);
  Serial.print("duty cycle: ");
  Serial.println(duty_cycle);
  Serial.println();

  delay(sampling_time);
}

vector3_double readSensors(){
  /*Call readSensor for each tactile sensor in the gripper.
  Calculate the maximum force measured in each axis.
  Return a vector of the max forces.

  :return: vector of maximum force in each axis.
  */
  vector3_double max_force;

  vector3_double finger1_force = finger1.readData();
  vector3_double finger2_force = finger2.readData();
  vector3_double finger3_force = finger3.readData();

  max_force.x = max(finger1_force.x, finger2_force.x);
  max_force.x = max(max_force.x, finger3_force.x);

  max_force.y = max(finger1_force.y, finger2_force.y);
  max_force.y = max(max_force.y, finger3_force.y);

  max_force.z = max(finger1_force.z, finger2_force.z);
  max_force.z = max(max_force.z, finger3_force.z);

  return max_force;
}

void resetServo(){
  servo.forward(255);

  while(digitalRead(11) == HIGH){
    //Wait until lower calibration button is pressed
  }

  servo.backward(255);
  delay(500);
  servo.off();
}