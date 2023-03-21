#include <NewPing.h>
#include "display.h"
#define TRIGGER_PIN  9 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int POWER_LVL = 40; //40
int POWER_OFFSET = 0; // offset for the power level of the motors gets added to the power level

const int InitRead[] = {A0, A1, A2, A3, A4}; //pins to read from the TCRT5000 sensors
const int InitOut[] = {12, 13, /*Direction A and B*/ 3, 11};// PWM A and B
const int Init7seg[] = {0, 1, 2, 4, 5, 6, 7, 8, A5};   // 7 segment display pins
const unsigned long pingInterval = 300; //interval between pings in milliseconds min is 29ms

static unsigned long pingTime = 0; // time of the last ping
int tcrtResult;

char DisplayA = '9';
char DisplayB = '0';

void ReadTCRT(); // function prototype
void Print(char displayA, char displayB); // function prototype
bool ReadSonic(); // function prototype
void RoadLogic(int SensorOut); // function prototype
void CountDown(); // in seconds

void Forward(int POWER_LVL); // function for moving forward
void Left(int POWER_LVL); // function for turning left
void Right(int POWER_LVL); // function for turning right
void Stop(int POWER_LVL); // function for stopping
void ScanIntersection(int POWER_LVL); // function for scanning the intersection
void Turn(int POWER_LVL); // function for rotating 180*
void Left_90(int POWER_LVL); // function for turning left
void Right_90(int POWER_LVL); // function for turning right

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
  for (int i = 0; i < 5; i++) {
    pinMode(InitRead[i], INPUT); //initialize the sensor input pins defined in the InitRead array.
  }
    for (int i = 0; i < 4; i++) {
    pinMode(InitOut[i], OUTPUT); //initialize the outputs for the motors
  }
     for (int i = 0; i < 9; i++) {
   pinMode(Init7seg[i], OUTPUT); //initialize the outputs the 7 segment display
  }
}

void loop() {
  currentMillis = millis(); // get the current time
  Print(DisplayA, DisplayB);
  
if (currentMillis > 11000) {
    if (currentMillis - pingTime >= pingInterval) { // check if it's time for another ping
      pingTime = currentMillis; // save the time of this ping
      if (ReadSonic()) { // check if the ultrasonic sensor is triggered
        Stop(POWER_LVL);
        currentAction = "Turning";
        DisplayA = '-';
        DisplayB = '-';
      }}    
    if (currentAction != "Turning" || currentAction != "Left_90" || currentAction != "Right_90") {
    ReadTCRT(); // read the TCRT5000 sensors
    RoadLogic(tcrtResult); // use the result of the TCRT5000 sensors to determine the next action
    }
  } else {
    CountDown();
  }
}

void ReadTCRT(){
  tcrtResult = 0;
  for (int i = 0; i < 5; i++) {
    //convert the binary number to decimal
    int val = analogRead(InitRead[i]);
    analogRead(InitRead[i]) > 20 ? val = 1 : val = 0;
    tcrtResult += (pow(2, i) * val);
    if (i >= 2 && digitalRead(InitRead[i]) == 1) {
      tcrtResult += 1;
    }
    }
    // DisplayA = tcrtResult / 10;
    // DisplayB = tcrtResult % 10;
  }



bool ReadSonic(){
  int distance = sonar.ping_cm(); // Send ping, get distance in cm and store result (0 = outside set distance range)
  if (distance < 10 && distance > 0) {
    return true;
  } else { // if the distance is greater than 10cm
    return false;
  }
}

void RoadLogic(int SensorOut){
  switch (SensorOut) {
  case 27:
    Forward(POWER_LVL);
    break;    
  case 30: case 29: case 25:
    Right(POWER_LVL);
    break;
  case 23: case 15: case 19:
    Left(POWER_LVL);
    break;  
  case 28: case 24: case 16:
    // Stop(POWER_LVL);
    // Left_90(POWER_LVL);
    // ScanIntersection(POWER_LVL);
    break;
  case 7: case 3: case 1:     //intersection to the left (b d e)
    Left_90(POWER_LVL);
    break;
  case 0:
    Turn(POWER_LVL);
    break;
  case 31:
  // delay(100);
  // Stop(POWER_LVL);
    break;
  default:
    break;
}
}

void Stop(int POWER_LVL){
  analogWrite(3, 0);  //Motor A
  analogWrite(11, 0); //Motor B
  digitalWrite(12, LOW); //Motor A
  digitalWrite(13, HIGH); //Motor B
  currentAction = "Stop";
}

void Forward(int POWER_LVL){
  analogWrite(3, POWER_LVL);  //Motor A
  analogWrite(11, POWER_LVL); //Motor B
  digitalWrite(12, LOW); //Motor A
  digitalWrite(13, HIGH); //Motor B
  currentAction = "Forward";
}

void Right(int POWER_LVL){
  analogWrite(3, 0);  //Motor A
  analogWrite(11, POWER_LVL + POWER_OFFSET); //Motor B
  digitalWrite(12, LOW); //Motor A
  digitalWrite(13, HIGH); //Motor B
  currentAction = "Right";
}

void Left(int POWER_LVL){
  analogWrite(3, POWER_LVL + POWER_OFFSET);  //Motor A
  analogWrite(11, 0); //Motor B
  digitalWrite(12, LOW); //Motor A
  digitalWrite(13, HIGH); //Motor B
  currentAction = "Left";
}

void Right_90(int POWER_LVL){
      analogWrite(3, POWER_LVL);
      analogWrite(11, POWER_LVL);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
      currentAction = "Right_90";
}

void Left_90(int POWER_LVL){
      analogWrite(3, POWER_LVL);
      analogWrite(11, POWER_LVL);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      currentAction = "Left_90";   
  }

void ScanIntersection(int POWER_LVL){
  /*type of intersections:
  *      |            |       |
  *   ---+---      ---|       |---      ---+---     ---+      +---
  *      |            |       |            |           |      |
  *      a            b       c            d           e      f
  * 
  * 
  * First check if road extends to the left: If it's true go left
  * Then check if road extends straight ahead: If yes go straight
  * Then check if road extends to the right: If yes go right
  */
 currentAction = "Scanning";
}

void Turn(int POWER_LVL){
  currentAction = "Turning";
  analogWrite(3, POWER_LVL);
  analogWrite(11, POWER_LVL);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void CountDown() {
  int sec = currentMillis / 1000;
  sec = 10 - sec;
  if (sec <= 0) {
    DisplayA = 's'; 
    DisplayB = 't';
  } else {
    DisplayA = sec / 10;
    DisplayB = sec % 10;
  }
}


