// Jack Chambers
// Assignment 7

#include "Vanduino.h"

int MOTOR_IN1 = 8;
int MOTOR_IN2 = 9;

// 0 forward
// 1 backward
int direction = 0;

// on/off
int running = 0;

int lastA = 0;

void changeMotorMode() {
  running = !running;
  if (running) {
    direction = !direction;
  }
}

void setup() {
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);

  pinMode(VANDUINO_SW3, INPUT);

  // digitalWrite(MOTOR_IN1, HIGH);
  // digitalWrite(MOTOR_IN2, LOW);
}

void loop() {
  int btnA = digitalRead(VANDUINO_SW3);

  if (lastA == HIGH && btnA == LOW) {
    changeMotorMode();
  };

  digitalWrite(MOTOR_IN1,   direction     && running);
  digitalWrite(MOTOR_IN2,   (!direction)  && running);

  lastA = btnA;
}
