#include "drive.h"
#include "sensor/sensor.h"
#include "display/display.h"

bool scan = false;
unsigned long delayStart = 0; // Time of the last delay
int waitTime = 0;
char displayA = ' ';
char displayB = ' ';

float POWER_OFFSET;

void Stop(int POWER_LVL){
  analogWrite(3, 0);  // Motor A
  analogWrite(11, 0); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void Forward(int POWER_LVL){
  POWER_OFFSET = 10;
  analogWrite(3, POWER_LVL);  // Motor A
  analogWrite(11, POWER_LVL); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void Right(int POWER_LVL){
  POWER_OFFSET = 10;
  analogWrite(3, POWER_LVL - POWER_OFFSET);  // Motor A
  analogWrite(11, POWER_LVL + POWER_OFFSET); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void Left(int POWER_LVL){
  POWER_OFFSET = 10;
  analogWrite(3, POWER_LVL + POWER_OFFSET);  // Motor A
  analogWrite(11, POWER_LVL - POWER_OFFSET); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void Right_90(int POWER_LVL){
      wait(300, 'r', 'i');
      analogWrite(3, POWER_LVL);
      analogWrite(11, POWER_LVL);
      digitalWrite(12, HIGH);
      digitalWrite(13, HIGH);
}

void Left_90(int POWER_LVL){
      wait(300, 'l', 'e');
      analogWrite(3, POWER_LVL);
      analogWrite(11, POWER_LVL);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW); 
  }

void ScanIntersection(int POWER_LVL){
  /*type of intersections:                                              
  *      |            |       |                                       =======       scan 2               
  *   ---+---      ---|       |---      ---+---     ---+      +---    ===+===       scan 1
  *      |            |       |            |           |      |          |
  *      1            2       3            4           5      6          7
  *     scan        left       scan       scan      left   scan         scan
  * check if its an end of parkour
  * First check if road extends to the left: If it's true go left   1 2 4 5
  * Then check if road extends straight ahead: If yes go straight   3
  * Then check if road extends to the right: If yes go right        6
  * 
  * 
  * 0 - 27
  * 28/24/16 - 27
  * 0 - 31
  * 28/24/16 - 31
  * 0 - 0
  */
scan = true;
 Stop(POWER_LVL);
 int SensorOut1 = ReadTCRT();
 unsigned long delayStart = millis();
 while (millis() - delayStart < 200) {
   Forward(POWER_LVL);
 }
Stop(POWER_LVL);
 int SensorOut2 = ReadTCRT();

 if (SensorOut1 == 0) {
    if (SensorOut2 == 0) {
      Stop(POWER_LVL);
      wait(1000, 'f', 'i');
    } else if (SensorOut2 == 27) {
      Left_90(POWER_LVL);
    } else if (SensorOut2 == 31) {
      Left_90(POWER_LVL);
    }
 } else if (SensorOut1 == 28 || SensorOut1 == 24 || SensorOut1 == 16) {
    if (SensorOut2 == 27) {
      Forward(POWER_LVL);
    } else if (SensorOut2 == 31) {
      Right_90(POWER_LVL);
    }
 }
scan = false;
}

void Turn_180(int POWER_LVL){
  wait(1800, 't', 'u');
  analogWrite(3, POWER_LVL);
  analogWrite(11, POWER_LVL);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

void Turn(int POWER_LVL){
  wait(50, 't', 'u');
  analogWrite(3, POWER_LVL);
  analogWrite(11, POWER_LVL);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}


bool wait(int delayTime, char a, char b){
  if (delayStart == 0 && delayTime != -1) {
    delayStart = millis();
    waitTime = delayTime;
    displayA = a;
    displayB = b;
    return true;
  } else if (millis() - delayStart >= waitTime && waitTime != 0) {
    delayStart = 0;
    return false;
  } else if (millis() - delayStart < waitTime && waitTime != 0) {
    Print(displayA, displayB);
    return true;
  } else {
    return false;
  }
}

bool isScanning(){
  if (scan == true) {
    return true;
  } else {
    return false;
  }
}