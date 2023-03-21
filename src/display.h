#include <Arduino.h>

String currentAction;
unsigned long currentMillis; // Time in ms
bool currentDisplay = 0;
unsigned long displayTimer = 0;

void Print(char displayA, char displayB);