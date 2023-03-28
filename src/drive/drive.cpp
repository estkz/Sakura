#include "drive.h"
#include "sensor/sensor.h"
#include "display/display.h"

unsigned long delayStart = 0; // Time of the last delay
int waitTime = 0;
char displayA = ' ';
char displayB = ' ';

float POWER_OFFSET;

void Stop(){
  analogWrite(3, 0);  // Motor A
  analogWrite(11, 0); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void Forward(int POWER_LVL){
  POWER_OFFSET = 0;
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
      wait(300);
      analogWrite(3, POWER_LVL); // Motor A 
      analogWrite(11, POWER_LVL); // Motor B
      digitalWrite(12, HIGH); //  Motor A
      digitalWrite(13, HIGH); // Motor B
}

void Left_90(int POWER_LVL){
      wait(300);
      analogWrite(3, POWER_LVL);  // Motor A
      analogWrite(11, POWER_LVL); //motor B
      digitalWrite(12, LOW);  // Motor A
      digitalWrite(13, LOW);  // Motor B
  }

void Turn_180(int POWER_LVL){
  wait(1200);
  analogWrite(3, POWER_LVL); // Motor A
  analogWrite(11, POWER_LVL); //motor B
  digitalWrite(12, HIGH); // Motor A 
  digitalWrite(13, HIGH); // Motor B
}

void Turn_left(int POWER_LVL){
  wait(50);
  analogWrite(3, POWER_LVL); // Motor A
  analogWrite(11, POWER_LVL);  // Motor A
  digitalWrite(12, LOW);  // Motor A
  digitalWrite(13, LOW); // Motor B
}

void Turn(int POWER_LVL){
  wait(50);
  analogWrite(3, POWER_LVL); // Motor A
  analogWrite(11, POWER_LVL); //motor B
  digitalWrite(12, HIGH); // Motor A
  digitalWrite(13, HIGH); // Motor B
}

void CriticalOffLeft(int POWER_LVL){
  POWER_OFFSET = 15;
  analogWrite(3, POWER_LVL + POWER_OFFSET);  // Motor A
  analogWrite(11, POWER_LVL - POWER_OFFSET); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
} 

void CriticalOffRight(int POWER_LVL){
  POWER_OFFSET = 15;
  analogWrite(3, POWER_LVL - POWER_OFFSET);  // Motor A
  analogWrite(11, POWER_LVL + POWER_OFFSET); // Motor B
  digitalWrite(12, LOW); // Motor A
  digitalWrite(13, HIGH); // Motor B
  
}

bool wait(int delayTime){
  //function to delay reading the TCRT5000 sensors
  if (delayStart == 0 && delayTime != -1) {
    delayStart = millis();
    waitTime = delayTime;
    return true;
  } else if (millis() - delayStart >= waitTime && waitTime != 0) {
    delayStart = 0;
    return false;
  } else if (millis() - delayStart < waitTime && waitTime != 0) {
    return true;
  } else {
    return false;
  }
}
