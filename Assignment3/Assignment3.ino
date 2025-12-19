// Jack Chambers
// Assignment 3
// 9/23/2025

// Display Controller
#include "Display.h"

// Vanduino Pin References
#include "Vanduino.h"

// 2a vars
int n = 0;

// 2b vars
int SAMPLE_DELAY = 1;
int SAMPLE_COUNT = 50;

// 3 vars
int DEBOUNCE_TIME = 50;
int timer = 0;
int count = 0;
int oldState = 0;
int pressed = 0;
int stale = 0;

void setup() {
	// put your setup code here, to run once:
	DISPLAY_setup();

	pinMode(VANDUINO_SW0, INPUT);
	pinMode(VANDUINO_SW1, INPUT);
	pinMode(VANDUINO_SW2, INPUT);
	pinMode(VANDUINO_SW3, INPUT);

	pinMode(VANDUINO_LED, OUTPUT);	
}

void loop() {
	// put your main code here, to run repeatedly

// Part 1
// int does_light = !digitalRead(VANDUINO_SW0) || !digitalRead(VANDUINO_SW1) || !digitalRead(VANDUINO_SW2) || !digitalRead(VANDUINO_SW3);
// digitalWrite(VANDUINO_LED, does_light);

// Part 2a
	// DISPLAY_clear();
	// DISPLAY_write(n);
	// n++;
	// if (n > 15) {
	// 	n = 0;
	// }
	// delay(500);

// Part 2b
	// if (!digitalRead(VANDUINO_SW0)) {
	// 	int start = millis();
	// 	int lastState = HIGH;
	// 	int bounces = 0;

	// 	while ((millis() - start) < SAMPLE_COUNT) {
	// 		int state = digitalRead(VANDUINO_SW0);

	// 		if (state != lastState) {
	// 			bounces++;
	// 			lastState = state;
	// 		}
	// 	}

	// 	DISPLAY_write(bounces);
	// }


// Part 3
	// int state = digitalRead(VANDUINO_SW0);
	
	// if (state == oldState) {
	// 	if (timer > DEBOUNCE_TIME) {
	// 		pressed = 1;
	// 	} else {
	// 		timer++;
	// 	}
	// } else {
	// 	timer = 0;
	// 	stale = 0;
	// 	pressed = 0;
	// }
	
	// if (pressed && !stale) {
	// 	stale = 1;
	// 	count++;
	// }
	
	// DISPLAY_write(count);
	

// Part 4
	// int reading = analogRead(VANDUINO_POT); // 1024 step ADC
	// int percentHex = map(reading, 0, 1024, 0, 15);

	// // does 0-99 instead of hex
	// DISPLAY_write(percentHex);
}
