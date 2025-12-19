// Debounce.cpp
// Jack Chambers
// 12/8/2025

#include "Buttons.h"
#include <Arduino.h>

int oldState[4]   = {0,0,0,0};
int pressed[4]    = {0,0,0,0};
int stale[4]      = {0,0,0,0};
int timer[4]      = {0,0,0,0};


void BUTTON_setup(int idx) {
  pinMode(BUTTON_IDX[idx], INPUT);
}

int BUTTON_db(int switchIdx) {
	return BUTTON_db(switchIdx, DEBOUNCE_TIME);
}


int BUTTON_db(int switchIdx, int debounceTime) {
  int state = digitalRead(BUTTON_IDX[switchIdx]);

  if (state == oldState[switchIdx]) {
    if (timer[switchIdx] > debounceTime) {
      pressed[switchIdx] = 1;
    } else {
      timer[switchIdx]++;
    }
  } else {
    timer[switchIdx] = 0;
    stale[switchIdx] = 0;
    pressed[switchIdx] = 0;
  }
  
  if (pressed[switchIdx] && !(stale[switchIdx])) {
    stale[switchIdx] = 1;
    return 1;
  }
  
  return 0;
}