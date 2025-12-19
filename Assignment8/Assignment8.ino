// Jack Chambers
// Combination Lock
// Servo + Keypad + LEDs

// Includes
#include <Servo.h>
#include "Keypad.h"

// Pins
int LEDA = 8;   // entering code
int LEDB = 9;   // locked
int LEDC = 10;  // unlocked
int SERVO = 11;


// Variables
Servo motor;
bool locked = false;
char COMBO[4] = {'1','2','3','4'};
char entered[4];
int codeIdx = 0;


void setLeds(int a, int b, int c) {
  digitalWrite(LEDA, a);
  digitalWrite(LEDB, b);
  digitalWrite(LEDC, c);
}


// All off, quick turn off
void allOff() {
  setLeds(0,0,0);
}


// Servo Close
// Red LED
void lockDoor() {
  motor.write(180);
  locked = true;
  setLeds(0,1,0);
  codeIdx = 0;
}


// Servo Open
// Green Led
void unlockDoor() {
  motor.write(0);
  locked = false;
  setLeds(0,0,1);
  codeIdx = 0;
}


// Blink red led
void codeFailed() {
  setLeds(0,1,0);
  codeIdx = 0;
  delay(1000);
  setLeds(0,0,0);
}


void setup() {
  KEYPAD_setup();

  // init leds
  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDC, OUTPUT);
  pinMode(SERVO, OUTPUT);

  // create servo
  motor.attach(SERVO);

  // Start open
  motor.write(0);
  setLeds(0,0,1);
}


void loop() {
  char key = KEYPAD_scanSteady();
  if (key == -1) return;

  // openened
  if (!locked) {
    if (key == 'A') {
      lockDoor();
    }
    return; // ignore all other keys
  }

  
  // closed
  if (key >= '0' && key <= '9') {
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDA, HIGH); // yellow LED on
    entered[codeIdx++] = key;
  }

  // code fully entered
  if (codeIdx == 4) {
    bool codePasses = true;

    // compare code
    for (int i = 0; i < 4; i++) {
      if (entered[i] != COMBO[i]) {
        codePasses = false;
        break;
      }
    }


    // unlock or code fail sequence
    if (codePasses) {
      unlockDoor();
    } else {
      // Wrong code
      codeFailed();
    }
  }
}
