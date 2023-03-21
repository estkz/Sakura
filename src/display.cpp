#include "display.h"

void Print(char displayA, char displayB){
      /*
  *          _a_
  *       f |  | b
  *          -g- 
  *       e |  | c
  *          -d- 
  * 
  */

  if (displayTimer < currentMillis) {
    displayTimer += 3;
    currentDisplay = !currentDisplay;
  if (currentDisplay == 1) {
    if (displayA == 0 || displayA == 2 || displayA == 3 || displayA == 5 || displayA == 6 || displayA == 7 || displayA == 8 || displayA == 9 || displayA == 's') {
      digitalWrite(0, HIGH);  //a
    } else {
      digitalWrite(0, LOW);  //a
    }

    if (displayA == 0 || displayA == 1 || displayA == 2 || displayA == 3 || displayA == 4 || displayA == 7 || displayA == 8 || displayA == 9) {
      digitalWrite(1, HIGH);  //b
    } else {
      digitalWrite(1, LOW);  //b
    }

    if (displayA == 0 || displayA == 1 || displayA == 3 || displayA == 4 || displayA == 5 || displayA == 6 || displayA == 7 || displayA == 8 || displayA == 9  || displayA == 's') {
      digitalWrite(5, HIGH);  //c
    } else {
      digitalWrite(5, LOW);  //c
    }

    if (displayA == 0 || displayA == 2 || displayA == 3 || displayA == 5 || displayA == 6 || displayA == 8 || displayA == 9 || displayA == 's' || displayA == 't'  ) {
      digitalWrite(6, HIGH);  //d
    } else {
      digitalWrite(6, LOW);  //d
    }

    if (displayA == 0 || displayA == 2 || displayA == 6 || displayA == 8 || displayA == 't') {
      digitalWrite(7, HIGH);  //e
    } else {
      digitalWrite(7, LOW);  //e
    }

    if (displayA == 0 || displayA == 4 || displayA == 5 || displayA == 6 || displayA == 8 || displayA == 9 || displayA == 's' || displayA == 't') {
      digitalWrite(8, HIGH);  //f
    } else {
      digitalWrite(8, LOW);  //f
    }

    if (displayA == 2 || displayA == 3 || displayA == 4 || displayA == 5 || displayA == 6 || displayA == 8 || displayA == 9 || displayB == '-' || displayA == 's' || displayA == 't' ) {
      digitalWrite(A5, HIGH);  //g
    } else {
      digitalWrite(A5, LOW);  //g
    }
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
  } else {
    if (displayB == 0 || displayB == 2 || displayB == 3 || displayB == 5 || displayB == 6 || displayB == 7 || displayB == 8 || displayB == 9 || displayB == 's') {
      digitalWrite(0, HIGH);  //a
    } else {
      digitalWrite(0, LOW);  //a
    }

    if (displayB == 0 || displayB == 1 || displayB == 2 || displayB == 3 || displayB == 4 || displayB == 7 || displayB == 8 || displayB == 9) {
      digitalWrite(1, HIGH);  //b
    } else {
      digitalWrite(1, LOW);  //b
    }

    if (displayB == 0 || displayB == 1 || displayB == 3 || displayB == 4 || displayB == 5 || displayB == 6 || displayB == 7 || displayB == 8 || displayB == 9 || displayB == 's' ) {
      digitalWrite(5, HIGH);  //c
    } else {
      digitalWrite(5, LOW);  //c
    }

    if (displayB == 0 || displayB == 2 || displayB == 3 || displayB == 5 || displayB == 6 || displayB == 8 || displayB == 9 || displayB == 's' || displayB == 't'  ) {
      digitalWrite(6, HIGH);  //d
    } else {
      digitalWrite(6, LOW);  //d
    }

    if (displayB == 0 || displayB == 2 || displayB == 6 || displayB == 8 || displayB == 't') {
      digitalWrite(7, HIGH);  //e
    } else {
      digitalWrite(7, LOW);  //e
    }

    if (displayB == 0 || displayB == 4 || displayB == 5 || displayB == 6 || displayB == 8 || displayB == 9 || displayB == 's' || displayB == 't' ) {
      digitalWrite(8, HIGH);  //f
    } else {
      digitalWrite(8, LOW);  //f
    }

    if (displayB == 2 || displayB == 3 || displayB == 4 || displayB == 5 || displayB == 6 || displayB == 8 || displayB == 9 || displayB == '-' || displayB == 's' || displayB == 't' ) {
      digitalWrite(A5, HIGH);  //g
    } else {
      digitalWrite(A5, LOW);  //g
    }
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
}}
}