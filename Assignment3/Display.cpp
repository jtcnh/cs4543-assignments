// Jack Chambers
// Display.cpp
// 9/24/2025
// Contains methods to control the 7 Segment display on the Vanduino

#include "Display.h"
#include <Arduino.h>

int CC_ENABLED = 0;

void DISPLAY_setup() {
	// Set up display pins for output
	pinMode(DISPLAY_A, OUTPUT);
	pinMode(DISPLAY_B, OUTPUT);
	pinMode(DISPLAY_C, OUTPUT);
	pinMode(DISPLAY_D, OUTPUT);
	pinMode(DISPLAY_E, OUTPUT);
	pinMode(DISPLAY_F, OUTPUT);
	pinMode(DISPLAY_G, OUTPUT);
	pinMode(DISPLAY_DP, OUTPUT);
}


void DISPLAY_enableCC() {
	CC_ENABLED = 1;
	pinMode(DISPLAY_CC1, OUTPUT);
	pinMode(DISPLAY_CC2, OUTPUT);
};


void DISPLAY_clear() {
	digitalWrite(DISPLAY_CC1, 	LOW);
	digitalWrite(DISPLAY_CC2, 	LOW);
	DISPLAY_reset();
}

void DISPLAY_reset() {
	digitalWrite(DISPLAY_A, 	LOW);
	digitalWrite(DISPLAY_B, 	LOW);
	digitalWrite(DISPLAY_C, 	LOW);
	digitalWrite(DISPLAY_D, 	LOW);
	digitalWrite(DISPLAY_E, 	LOW);
	digitalWrite(DISPLAY_F, 		LOW);
	digitalWrite(DISPLAY_G, 	LOW);
	digitalWrite(DISPLAY_DP, 	LOW);
}


void DISPLAY_setDecimal(int on) {
	digitalWrite(DISPLAY_DP, on);
}


// Uses SW0 and SW1 pins
// Must bridge connection between S & C (source & cathode)
void DISPLAY_writeSeperate(int leftNibble, int rightNibble) {

	// If CC's aren't enabled, just display the left digit
	if (!CC_ENABLED) {
		DISPLAY_write(leftNibble);
		return;
	}

	DISPLAY_write(leftNibble);
	digitalWrite(DISPLAY_CC1, LOW);
	digitalWrite(DISPLAY_CC2, HIGH);

	delay(10);
	
	DISPLAY_write(rightNibble);
	digitalWrite(DISPLAY_CC2, LOW);
	digitalWrite(DISPLAY_CC1, HIGH);

	delay(10);
}


void DISPLAY_write(int nibble) {
	int truncated = nibble % 16;
	
	DISPLAY_reset();

	switch (truncated) {
		case 0:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			break;
		
		case 1:
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			break;
			
		case 2:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			break;
			
		case 3:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			break;
			
		case 4:
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			break;
			
		case 5:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			break;
			
		case 6:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			break;
			
		case 7:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			break;
			
		case 8:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 9:
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 10: // A
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 11: // B
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 12: // C
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			break;
			
		case 13: // D
			digitalWrite(DISPLAY_B, HIGH);
			digitalWrite(DISPLAY_C, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 14: // E
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_D, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
			
		case 15: // F
			digitalWrite(DISPLAY_A, HIGH);
			digitalWrite(DISPLAY_E, HIGH);
			digitalWrite(DISPLAY_F, HIGH);
			digitalWrite(DISPLAY_G, HIGH);
			break;
	}
	
}