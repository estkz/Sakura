#include "display.h"
bool currentDisplay = 0;
unsigned long displayTimer = 0;

void Print(char displayA, char displayB) {
  /*         aaaa
  *         f    b
  *         f    b
  *          gggg
  *         e    c
  *         e    c
  *          dddd   */
  char display;
  if (currentDisplay == 1) {
    display = displayB;
  } else {
    display = displayA;
  }
  if (displayTimer < millis()) {
    displayTimer += 3;
    currentDisplay = !currentDisplay;
    if (display == 0 || display == 2 || display == 3 || display == 5 || display == 6 || display == 7 || display == 8 || display == 9 || display == 's' || display == 'e' || display == 'r') {
      digitalWrite(0, HIGH);  // a
    } else {
      digitalWrite(0, LOW);  // a
    }

    if (display == 0 || display == 1 || display == 2 || display == 3 || display == 4 || display == 7 || display == 8 || display == 9 || display == 'r') {
      digitalWrite(1, HIGH);  // b
    } else {
      digitalWrite(1, LOW);  // b
    }

    if (display == 0 || display == 1 || display == 3 || display == 4 || display == 5 || display == 6 || display == 7 || display == 8 || display == 9  || display == 's' || display == 'u' || display == 'r' || display == 'i') {
      digitalWrite(5, HIGH);  // c
    } else {
      digitalWrite(5, LOW);  // c
    }

    if (display == 0 || display == 2 || display == 3 || display == 5 || display == 6 || display == 8 || display == 9 || display == 's' || display == 't' || display == 'u' || display == 'l' || display == 'e' || display == 'c' ) {
      digitalWrite(6, HIGH);  // d
    } else {
      digitalWrite(6, LOW);  // d
    }

    if (display == 0 || display == 2 || display == 6 || display == 8 || display == 't' || display == 'u' || display == 'l' || display == 'r' || display == 'e' || display == 'c' ) {
      digitalWrite(7, HIGH);  // e
    } else {
      digitalWrite(7, LOW);  // e
    }

    if (display == 0 || display == 4 || display == 5 || display == 6 || display == 8 || display == 9 || display == 's' || display == 't' || display == 'l' || display == 'e' || display == 'r') {
      digitalWrite(8, HIGH);  // f
    } else {
      digitalWrite(8, LOW);  // f
    }

    if (display == 2 || display == 3 || display == 4 || display == 5 || display == 6 || display == 8 || display == 9 || displayB == '-' || display == 's' || display == 't' || display == 'e' || display == 'r' || display == 'c'  ) {
      digitalWrite(A5, HIGH);  // g
    } else {
      digitalWrite(A5, LOW);  // g
    }

    if (currentDisplay == 1) {
          digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    } else {
           digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    }
  }}

  void CountDown(unsigned long currentMillis) {
  int sec = currentMillis / 1000;
  sec = 10 - sec;
  if (sec <= 0) {
    Print('s', 't');
  } else {
    Print(sec / 10, sec % 10);
  }
}