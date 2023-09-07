#include "ServoBD.h"
#include "PID.h"
#include "TactileSensor.h"
#include <Wire.h>
#include "vector3.h"

//Servo
ServoBD servo(5, 6);

//PID Controller
PID pid(1, 0, 5);

//Sensors
TactileSensor finger1(1);
//TactileSensor finger2(2);
//TactileSensor finger3(2);

double Fz_target = 1.50;     //Target Z force [N]
int sampling_time = 100;     //Sampling time [ms]
int ut_max;

uint8_t duty_cycle_max = 255;
uint8_t duty_cycle_min = 200;

void setup(){
  pinMode(9, INPUT_PULLUP);   //Set PIN09 to input. PIN09 for NED input
  pinMode(10, INPUT_PULLUP);  //Set PIN10 to input using the internal pull-up resistor. PIN10 for start/stop button
  pinMode(11, INPUT_PULLUP);  //Set PIN11 to input using the internal pull-up resistor. PIN11 for lower calibration bound button
  pinMode(12, INPUT_PULLUP);  //Set PIN12 to input using the internal pull-up resistor. PIN12 for upper calibration bound button
  Wire.begin();               //Initialize I2C connection
  Serial.begin(9600);         //Initialize serial monitor
  
  delay(100);

  ut_max = pid.calculate(Fz_target, 0);

  //Initialize finger objects
  Serial.println("Initializing Fingers");
  finger1.init();
  //finger2.init();
  //finger3.init();

  Serial.print("Resetting Servo...");
  resetGripper(255);
  Serial.println("Servo Reset");

  Serial.print("System ready to start...");
  
  Serial.println("Starting System");
  Serial.println();

  fullOpenGripper();

  unsigned long t0 = millis();
  while(digitalRead(10) == HIGH && digitalRead(9) == HIGH){
    //Pause until start button is pressed or 5 seconds pass
    if(millis()-t0 >= 5000){
      break;
    }
  }
}

void loop(){
  /*Main Control Loop.
  Read sensor data then calculate control output using PID controller.
  If control output is positive rotate servo forward, else rotate it backwards.
  If control output is 0, stop servo.

  Delay by sampling time T.

  :return: None
  */

  //If the button connected to pin 10 is pressed OR the NED sends a signal to pin 9, the servo will be reset and the control loop will stop
  /*if(digitalRead(10) == LOW || digitalRead(9) == HIGH){ 
    Serial.println("STOPPING SYSTEM");
    Serial.println("Press Arduino Reset button to restart system");
    return;
  }*/

  //Read sensor data and return vector of largest force in each axis
  vector3_double max_force = readSensors();

  //Calculate control output
  int ut = pid.calculate(Fz_target, max_force.z);  
  
  uint8_t duty_cycle = uint8_t((((abs(ut) - 0)*(duty_cycle_max - duty_cycle_min)) / (ut_max - 0)) + duty_cycle_min); //Convert ut to duty cycle value range (200 to 255);

  //Rotate servo
  if(ut > 0 && digitalRead(12) == HIGH){
    //Close Gripper
    servo.backward(duty_cycle);
  }
  else{
    servo.off();
  }

  //Print force, u(t), and duty_cycle data
  /*Serial.print("xForce: ");
  Serial.println(max_force.x);
  Serial.print("yForce: ");
  Serial.println(max_force.y);*/
  //Serial.print("zForce: ");
  Serial.println(max_force.z);
  //Serial.print("u(t): ");
  //Serial.println(ut);
  //Serial.print("duty cycle: ");
  //Serial.println(duty_cycle);
  //Serial.println();

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
  /*vector3_double finger2_force = finger2.readData();
  vector3_double finger3_force = finger3.readData();

  
  max_force.x = max(finger1_force.x, finger2_force.x);
  max_force.x = max(max_force.x, finger3_force.x);

  max_force.y = max(finger1_force.y, finger2_force.y);
  max_force.y = max(max_force.y, finger3_force.y);

  max_force.z = max(finger1_force.z, finger2_force.z);
  max_force.z = max(max_force.z, finger3_force.z);
  */
  max_force = finger1_force;

  max_force.x = round(max_force.x/100);
  max_force.y = round(max_force.y/100);
  max_force.z = round(max_force.z/100);

  return max_force;
}

void resetGripper(byte duty_cycle){
  /*Reset servo position by centering pinion in rack.
  Servo finds lower gripper bound, then finds highest gripper bound and records travel time.
  Then rotates back half the time to find the center of the rack.

  :return: None
  */
  servo.forward(duty_cycle);
  while(digitalRead(11) == HIGH){
    //Wait until lower bound calibration button is pressed
  }
  unsigned long t0 = millis();

  servo.backward(duty_cycle);
  while(digitalRead(12) == HIGH){
    //Wait until upper bound calibration button is pressed
  }
  unsigned long t1 = millis();
  unsigned long tc = round((t1 - t0)/2);
  
  servo.forward(duty_cycle);
  delay(tc);
  servo.off();
}

void fullOpenGripper(){
  servo.forward(255);
  while(digitalRead(11) == HIGH){
    //Wait until lower bound calibration button is pressed
  }
  servo.backward(255);
  delay(10);
  servo.off();
}
