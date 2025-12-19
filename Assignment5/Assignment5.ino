// Jack Chambers
// Assignment 5
// 9/23/2025

// Constants
#define BLANK -1   // value outside 0–F used to indicate blank digit

// Display Controller
#include "Display.h"
#include "Vanduino.h"

void setup() {
	// put your setup code here, to run once:
	DISPLAY_setup();
    DISPLAY_enableCC();

	pinMode(VANDUINO_LED, OUTPUT);
    pinMode(VANDUINO_SW2, INPUT);
    pinMode(VANDUINO_SW3, INPUT);
}

void display(int value, char base, char blanking)
{
    int left = 0;
    int right = 0;

    // Clamp value to valid range
    if (base == 0) {               // Decimal
        if (value < 0) value = 0;
        if (value > 99) value = 99;

        left  = value / 10;
        right = value % 10;

        if (blanking == 0 && value < 10) {
            left = BLANK;          // suppress leading zero
        }
    }

    else {                          // Hexadecimal
        if (value < 0) value = 0;
        if (value > 0xFF) value = 0xFF;

        left  = (value >> 4) & 0x0F;
        right = value & 0x0F;

        if (blanking == 0 && value < 0x10) {
            left = BLANK;
        }
    }

   	DISPLAY_write(left, right);
}


void loop() {
	// Assignment 4
	int reading = analogRead(VANDUINO_POT); // 1024 step ADC

    int percentDecimal  = map(reading, 0, 1024, 0, 100);
	int percentHex      = map(reading, 0, 1024, 0, 256);

    int base = digitalRead(VANDUINO_SW2);
    int blank = digitalRead(VANDUINO_SW3);;

    if (base == 0) { // decimal
        display(percentDecimal, base, blank);
    } else {
        display(percentHex, base, blank);
    }
}




