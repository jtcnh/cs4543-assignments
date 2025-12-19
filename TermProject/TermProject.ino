// Term Project
// Jack Chambers

#include "Display.h"
#include "Buttons.h"
#include "Vanduino.h"

// Types
typedef enum {
  LOCKED,
  UNLOCKED,
  SET,
  FAILED,
  CODESET
} LockState;

// Constants
int charL[7] = { 0, 0, 0, 1, 1, 1, 0 };
int charS[7] = { 1, 0, 1, 1, 0, 1, 1 };
int charU[7] = { 0, 1, 1, 1, 1, 1, 0 };
int charP[7] = { 1, 1, 0, 0, 1, 1, 1 };
int charF[7] = { 1, 0, 0, 0, 1, 1, 1 };
int charA[7] = { 1, 1, 1, 0, 1, 1, 1 };
int charC[7] = { 1, 0, 0, 1, 1, 1, 0 };

// Variables
int code[4] = { 0, 0, 0, 0 };

// lock state
int enteredDigits[4] = { 0, 0, 0, 0 };
int enterIdx = 0;
int edt = 0;  // enter display toggle

// Set state
int setDigits[4] = { 0, 0, 0, 0 };
int setIdx = 0;
int sdt = 0;  // set display toggle

// unlocked state
int led = 0;

// states 0-locked 1-unlocked 2-set
LockState state = LOCKED;
LockState failReturn = LOCKED;
int stateTimer = 0;

int compareCodes() {
  int success = 1;
  for (int i=0; i<4; i++) {
    int enter = enteredDigits[i];
    int pair = code[i];
    int equal = (enter == pair);

    success = success & equal;
  }
  return success;
}


void resetCode() {
  enterIdx = 0;
}


void loadSetCode() {
  setIdx = 0;
  for (int i=0; i<4; i++) {
    code[i] = setDigits[i];
  }
}


void setup() {
  DISPLAY_enableCC();
  DISPLAY_setup();
  BUTTON_setup(2);
  BUTTON_setup(3);
  pinMode(VANDUINO_LED, OUTPUT);
}


void loop() {
  // Locked State
  int reading = analogRead(VANDUINO_POT);  // 1024 step ADC
  char nextState = state;



  // Locked
  if (state == LOCKED) {
    int selectedDigit = map(reading, 0, 1024, 0, 10);

    // select digit
    if (BUTTON_db(2)) {
      if (enterIdx > 1) {
        enteredDigits[enterIdx-1] = selectedDigit;
      }
      enterIdx++;
    }

    // reset entry
    if (BUTTON_db(3)) {
      enterIdx = 0;
    }

    // code entry complete
    if (enterIdx == 5) {
      if (compareCodes() == 1) {
        nextState = UNLOCKED;
      } else {
        nextState = FAILED;
        failReturn = LOCKED;
      }

      resetCode();
    
    // code entry in progress
    } else if (enterIdx > 0) {
      // toggle between 'L' and 'enterIdx'
      if (stateTimer % 50 == 0) {
        edt =! edt;
      }

      // display toggle
      if (edt) {
        DISPLAY_write(charL, selectedDigit);
      } else {
        DISPLAY_write(enterIdx, selectedDigit);
      }

    // generic locked state "L digit"
    } else {
      DISPLAY_write(charL, selectedDigit);
    }
  


  // Unlocked
  } else if (state == UNLOCKED) {
    int unlockMode = map(reading, 0, 1024, 0, 4);

    // Unlocked option switch

    // UNLOCKED NOOP
    if (unlockMode == 0) {
      DISPLAY_write(charU, -1);

    // UNLOCKED ACTION
    } else if (unlockMode == 1) {
      DISPLAY_write(charU, charA);

      // light LED as "action"
      if (BUTTON_db(2) == 1) {
        led =! led;
      }
      digitalWrite(VANDUINO_LED, led);
    
    // UNLOCKED SET CODE
    } else if (unlockMode == 2) {
      DISPLAY_write(charU, charS);

      // goto set state
      if (BUTTON_db(2)) {
        nextState = SET;
      }

    // UNLOCKED LOCK
    } else if (unlockMode == 3) {
      DISPLAY_write(charU, charL);

      // goto lock state
      if (BUTTON_db(2)) {
        nextState = LOCKED;
      }
    }
    


  // Set Mode
  } else if (state == SET) {
    int selectedDigit = map(reading, 0, 1024, 0, 10);

    // select digit
    if (BUTTON_db(2)) {
      if (setIdx > 1) {
        setDigits[setIdx-1] = selectedDigit;
      }
      setIdx++;
    }

    // reset entry
    if (BUTTON_db(3)) {
      // go back to unlock
      if (setIdx == 0) {
        nextState = UNLOCKED;
      
      // reset set code
      } else {
        setIdx = 0;
      }
    }

    // set code entry complete
    if (setIdx == 5) {
      loadSetCode();
      nextState = CODESET;
    
    // code entry in progress
    } else if (setIdx > 0) {
      // toggle between 'L' and 'setIdx'
      if (stateTimer % 50 == 0) {
        sdt =! sdt;
      }

      // display toggle
      if (sdt) {
        DISPLAY_write(charS, selectedDigit);
      } else {
        DISPLAY_write(setIdx, selectedDigit);
      }

    // generic locked state "L digit"
    } else {
      DISPLAY_write(charS, selectedDigit);
    }



  // fail entry state
  } else if (state == FAILED) {
    DISPLAY_write(charF, -1);
    if (stateTimer > 100) {
      nextState = failReturn;
    }

  // code set message
  } else if (state == CODESET) {
    DISPLAY_write(charC, charS);
    if (stateTimer > 100) {
      nextState = UNLOCKED;
    }
  }

  // State Machine
  if (nextState == state) {
    stateTimer++;
  } else {
    stateTimer = 0;
    state = nextState;
  }
}
