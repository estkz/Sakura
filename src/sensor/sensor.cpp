#include "sensor.h"
#include <NewPing.h>
#include "display/display.h"
#include "drive/drive.h"

const int InitRead[] = {A0, A1, A2, A3, A4};

int ReadTCRT(){
  int tcrtResult = 0;
  for (int i = 0; i < 5; i++) {
    // Convert the binary number to decimal
    int val = analogRead(InitRead[i]);
    analogRead(InitRead[i]) > 20 ? val = 1 : val = 0;
    tcrtResult += (pow(2, i) * val);
    if (i >= 2 && digitalRead(InitRead[i]) == 1) {
      tcrtResult += 1;
    }
    }
    Print(tcrtResult/10, tcrtResult%10);
    return tcrtResult;
  }



bool ReadSonic(NewPing sonar){
  int distance = sonar.ping_cm(); // Send ping, get distance in cm and store result (0 = outside set distance range)
  if (distance < 10 && distance > 0) {
    return true;
  } else { // If the distance is greater than 10cm
    return false;
  }
}
