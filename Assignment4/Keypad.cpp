// Jack Chambers
// Keypad.cpp
// 11/18/2025
// Module for reading from the keypad

/*
Make sure to connect the cable and all that correctly!
Correct cable orientation:
	Cable goes across the display southward
	Connects to keypad upside down
*/

/*

!! Vanduino Conflicts !!
	Serial (D0, D1)
	Display (D0 - D7)

*/

#include "Keypad.h"
#include <Arduino.h>

const char NO_RESULT = -1;
const unsigned long debounceDelay = 15; // ms

// Setup the keypad IO for arduino
void KEYPAD_setup() {
	// set rows as outputs
	for (int i=0; i < 4; i++) {
		int pin = KEYPAD_ROW[i];
		pinMode(pin, OUTPUT);
		//digitalWrite(pin, HIGH);
	}
	
	// set columns as inputs
	for (int i=0; i < 4; i++) {
		int pin = KEYPAD_COL[i];
		pinMode(pin, INPUT);
	}
}


// Returns the first encountered key press from KEY_MAPPING
// Mapping is found in Keypad.h and can be customized
char KEYPAD_scanRaw() {
	// scan rows
	for (int row=0; row < 4; row++) {
		// get the io pin for the row
		int rowPin = KEYPAD_ROW[row];
		digitalWrite(rowPin, HIGH);
		
		// scan the columns
		char pressed = NO_RESULT;
		for (int col=0; col < 4; col++) {
			// get the column io pin and read it 
			int colPin = KEYPAD_COL[col];
			int reading = digitalRead(colPin);
			
			// 
			if (reading == 1) {
				pressed = KEYPAD_MAP[row][col];
			}
		}

		digitalWrite(rowPin, LOW);
		if (pressed != NO_RESULT) {
			return pressed;
		}
	}
	return NO_RESULT;
}



// Debounced keypad scanner
// Returns a key only once per physical press
char KEYPAD_scanSteady() {
	static char lastKey = NO_RESULT;
	static unsigned long lastChangeTime = 0;

	char currentKey = KEYPAD_scanRaw();

	// Key state changed
	if (currentKey != lastKey) {
		lastChangeTime = millis();
		lastKey = currentKey;
		return NO_RESULT;
	}

	// Key has been stable long enough
	if (currentKey != NO_RESULT && (millis() - lastChangeTime) >= debounceDelay) {

		// Wait until key is released before allowing another press
		while (KEYPAD_scanRaw() == currentKey) {
			delay(1);
		}

		lastKey = NO_RESULT;
		return currentKey;
	}

	return NO_RESULT;
}
