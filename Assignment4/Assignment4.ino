// Assignment 3 
// Jack Chambers
// 11/24/2025
// Keypad Scanner Implementation

// Keypad Controller
#include "Keypad.h"
#include "Display.h"
#include "Vanduino.h"

int state = 0;
char pressed = -1;

void displayChar(char x) {
	switch (x) {
		case '0':
			DISPLAY_write(0);
			break;

		case '1':
			DISPLAY_write(1);
			break;

		case '2':
			DISPLAY_write(2);
			break;

		case '3':
			DISPLAY_write(3);
			break;

		case '4':
			DISPLAY_write(4);
			break;

		case '5':
			DISPLAY_write(5);
			break;

		case '6':
			DISPLAY_write(6);
			break;

		case '7':
			DISPLAY_write(7);
			break;

		case '8':
			DISPLAY_write(8);
			break;

		case '9':
			DISPLAY_write(9);
			break;

		case 'A':
			DISPLAY_write(10);
			break;

		case 'B':
			DISPLAY_write(11);
			break;

		case 'C':
			DISPLAY_write(12);
			break;

		case 'D':
			DISPLAY_write(13);
			break;

		case '*':
			DISPLAY_write(14);
			break;

		case '#':
			DISPLAY_write(15);
			break;
	}
}

void setup() {

}

void loop() {
	// flip
	state = 1 - state;


	if (state == 0) {
		KEYPAD_setup();
		pressed = KEYPAD_scanSteady();
	} else {
		DISPLAY_setup();
		displayChar(pressed);
		delay(250);
	}
}
