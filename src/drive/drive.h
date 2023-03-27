#include <Arduino.h>

void Forward(int POWER_LVL); // Function for moving forward
void Left(int POWER_LVL); // Function for turning left
void Right(int POWER_LVL); // Function for turning right
void Stop(); // Function for stopping
void ScanIntersection(int POWER_LVL); // Function for scanning the intersection
void Turn_left(int POWER_LVL); // Function for rotating
void Turn(int POWER_LVL); // Function for rotating
void Turn_180(int POWER_LVL); // Function for rotating 180*
void Left_90(int POWER_LVL); // Function for turning left
void Right_90(int POWER_LVL); // Function for turning right

bool wait(int delayTime); // Function prototype
bool isScanning(); // Function prototype