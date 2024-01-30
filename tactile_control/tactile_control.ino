#include "ServoBD.h"
#include "PID.h"
#include "TactileSensor.h"
#include "Wire.h"
#include "vector3.h"

//Servo
ServoBD servo(5, 6);

//PID Controller
PID pid(1, 0, 5);

//Sensors
TactileSensor finger1(1);
//TactileSensor finger2(2);
//TactileSensor finger3(2);

double fzTarget = 1.50;     //Target Z force [N]
int samplingTime = 100;     //Sampling time [ms]
int utMax;

int dutyCycleMax = 255;
int dutyCycleMin = 200;

void setup(){
  pinMode(9, INPUT_PULLUP);   //Set PIN09 to input. PIN09 for NED input
  pinMode(10, INPUT_PULLUP);  //Set PIN10 to input using the internal pull-up resistor. PIN10 for start/stop button
  pinMode(11, INPUT_PULLUP);  //Set PIN11 to input using the internal pull-up resistor. PIN11 for lower calibration bound button
  pinMode(12, INPUT_PULLUP);  //Set PIN12 to input using the internal pull-up resistor. PIN12 for upper calibration bound button
  Wire.begin();               //Initialize I2C connection
  Serial.begin(9600);         //Initialize serial monitor
  
  delay(100);

  utMax = pid.calculate(fzTarget, 0);

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
  
  //Read sensor data and return vector of largest force in each axis
  vector3<long> maxForce = readSensors();

  //Calculate control output
  int ut = pid.calculate(fzTarget, maxForce.z);  
  int dutyCycle = (((abs(ut) - 0)*(dutyCycleMax - dutyCycleMin)) / (utMax - 0)) + dutyCycleMin; //Convert ut to duty cycle value range (200 to 255);

  //Rotate servo
  if(ut > 0 && digitalRead(12) == HIGH){
    //Close Gripper
    servo.pwm(-dutyCycle);
  }
  else{
    servo.pwm(0);
  }

  //Print force, u(t), and dutyCycle data
  /*Serial.print("xForce: ");
  Serial.println(maxForce.x);
  Serial.print("yForce: ");
  Serial.println(maxForce.y);*/
  //Serial.print("zForce: ");
  Serial.println(maxForce.z);
  //Serial.print("u(t): ");
  //Serial.println(ut);
  //Serial.print("duty cycle: ");
  //Serial.println(dutyCycle);
  //Serial.println();

  delay(samplingTime);
}

vector3<long> readSensors(){
  /*Call readSensor for each tactile sensor in the gripper.
  Calculate the maximum force measured in each axis.
  Return a vector of the max forces.

  :return: vector of maximum force in each axis.
  */
  vector3<long> maxForce;

  vector3<long> finger1Force = finger1.readData();
  /*vector3_double finger2Force = finger2.readData();
  vector3_double finger3Force = finger3.readData();

  
  maxForce.x = max(finger1Force.x, finger2Force.x);
  maxForce.x = max(maxForce.x, finger3Force.x);

  maxForce.y = max(finger1Force.y, finger2Force.y);
  maxForce.y = max(maxForce.y, finger3Force.y);

  maxForce.z = max(finger1Force.z, finger2Force.z);
  maxForce.z = max(maxForce.z, finger3Force.z);
  */
  maxForce = finger1Force;
  maxForce /= 100;

  return maxForce;
}

void resetGripper(byte dutyCycle){
  /*Reset servo position by centering pinion in rack.
  Servo finds lower gripper bound, then finds highest gripper bound and records travel time.
  Then rotates back half the time to find the center of the rack.

  :return: None
  */
  servo.pwm(dutyCycle);
  while(digitalRead(11) == HIGH){
    //Wait until lower bound calibration button is pressed
  }
  unsigned long t0 = millis();

  servo.pwm(-dutyCycle);
  while(digitalRead(12) == HIGH){
    //Wait until upper bound calibration button is pressed
  }
  unsigned long t1 = millis();
  unsigned long tc = round((t1 - t0)/2);
  
  servo.pwm(dutyCycle);
  delay(tc);
  servo.pwm(0);
}

void fullOpenGripper(){
  servo.pwm(255);
  while(digitalRead(11) == HIGH){
    //Wait until lower bound calibration button is pressed
  }
  servo.pwm(-255);
  delay(10);
  servo.pwm(0);
}
