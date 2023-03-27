#include <NewPing.h>
#include "display/display.h"
#include "sensor/sensor.h"
#include "drive/drive.h"

#define TRIGGER_PIN  9 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int POWER_LVL = 35; //40

const int InitRead[] = {A0, A1, A2, A3, A4}; // Pins to read from the TCRT5000 sensors
const int InitOut[] = {12, 13, /*Direction A and B*/ 3, 11};// PWM A and B
const int Init7seg[] = {0, 1, 2, 4, 5, 6, 7, 8, A5};   // 7 segment display pins

const unsigned long pingInterval = 300; // Interval between pings in milliseconds min is 29ms

static unsigned long pingTime = 0; // Time of the last ping
unsigned long currentMillis; // Time in milliseconds
unsigned long startTime = 0;
int SensorOut; // Variable to store the result of the TCRT5000 sensor
bool detectEnd = true; // Variable to store the result of the ultrasonic sensor

void RoadLogic(int SensorOut); // Function prototype
bool DetectEnd(); // Function prototype

int intersectionType = 0; // Variable to store the type of intersection

void setup() {
  TCCR2B = TCCR2B & B11111000 | B00000111; // For PWM frequency of 30.64 Hz
  for (int i = 0; i < 5; i++) {
    pinMode(InitRead[i], INPUT); // Initialize the sensor input pins defined in the InitRead array.
  }
    for (int i = 0; i < 4; i++) {
    pinMode(InitOut[i], OUTPUT); // Initialize the outputs for the motors
  }
     for (int i = 0; i < 9; i++) {
   pinMode(Init7seg[i], OUTPUT); // Initialize the outputs the 7 segment display
  }
}

void loop() {
if (detectEnd == true) {
  currentMillis = millis(); // Get the current time
  if (currentMillis > 11/*000*/) {
      if (currentMillis - pingTime >= pingInterval) { // Check if it's time for another ping
        pingTime = currentMillis; // Save the time of this ping
        if (ReadSonic(sonar)) { // Check if the ultrasonic sensor is triggered
          Turn_180(POWER_LVL);
        }}
      SensorOut = ReadTCRT(); // Read the TCRT5000 sensor 
      if (wait(-1) == false && isScanning() == false) {
      RoadLogic(SensorOut); // Use the result of the TCRT5000 sensors to determine the next action
      }
    } else {
      CountDown(currentMillis);
    }
    detectEnd = DetectEnd();
  } else {
    Stop();
    Print('-','-');
  }
  
}

void RoadLogic(int SensorOut){
  switch (SensorOut) {
  case 27: case 25: case 19:
    Forward(POWER_LVL);
    break;    
  case 30: case 29:
    Right(POWER_LVL);
    break;
  case 23: case 15:
    Left(POWER_LVL);
    break;  
  case 7: case 3: case 1:
    Left_90(POWER_LVL);
    break;
  case 0:     // Intersection to the left (2 or 5)
    // Forward(POWER_LVL);
    // wait(300);
    Turn_left(POWER_LVL);
  case 28: case 24: case 16:    // Intersection to the right (1, 3, 4 or 6)
    Forward(POWER_LVL);
    break;
  case 31:
    wait(50);
    Turn(POWER_LVL); // Turn right
    break;
  default:
    break;
}
}

// wait before turning
// 16, 17, 0 of 1

bool DetectEnd(){
  if (ReadTCRT() == 0 || ReadTCRT() == 1 || ReadTCRT() == 16 && startTime != 0) {
    if (millis() - startTime >= 300) {
      return false;
    } else {
      return true;
    }
  } else {
    startTime = millis();
    return true;
  }
}

