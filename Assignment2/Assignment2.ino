// Assignment 2
// Jack Chambers
// 11/24/2025

#include "Vanduino.h"
#include "Display.h"

const int DISPLAY_SEGMENTS[8] = {
  DISPLAY_A,
  DISPLAY_B,
  DISPLAY_C,
  DISPLAY_D,
  DISPLAY_E,
  DISPLAY_F,
  DISPLAY_G,
  DISPLAY_DP
};

void setup() {
  DISPLAY_setup();
  pinMode(VANDUINO_LED, OUTPUT);
}

void loop() {
  BlinkSequence();
  delay(250);

  DisplaySequence();
  delay(250);

  DisplayAllOn();
  delay(250);
}


void BlinkSequence() {
  int ledState = 0;
  for (int i=0; i<8; i++) {
    ledState = 1 - ledState;
    digitalWrite(VANDUINO_LED, ledState);
    delay(500);
  }
}

void DisplaySequence() {
  int lastSegment = -1;
  for (int i=0; i < 8; i++) {
    DISPLAY_reset();
    digitalWrite(DISPLAY_SEGMENTS[i], 1);
    delay(500);
  }
}

void DisplayAllOn() {
  int state = 0;
  int lastSegment = -1;
  
  for (int j=0; j<8; j++) {
    state = 1 - state;
    
    DISPLAY_reset();
    if (state == 1) {
      DISPLAY_write(8);
      DISPLAY_setDecimal(HIGH);
    }

    delay(500);
  }
}