// Jack Chambers
// Display.h
// 9/24/2025
// Contains header info for 7seg display on vanduino

/*

!! Vanduino Conflicts !!
	Serial (D0, D1)
	Keypad (D0 - D7)

*/


#ifndef __DISPLAY_H__
#define __DISPLAY_H__

// Display Pins
#define DISPLAY_A 0 // NOTE: A & B overwrite serial comm (pins 0-1)
#define DISPLAY_B 1
#define DISPLAY_C 2
#define DISPLAY_D 3
#define DISPLAY_E 4
#define DISPLAY_F 5
#define DISPLAY_G 6
#define DISPLAY_DP 7

const int DISPLAY_CUSTOM_ORDER[7] = {0,1,2,3,4,5,6};

// Display Pullup Resistors
#define DISPLAY_CC1 9 // Shares with SW1
#define DISPLAY_CC2 8 // Shares with SW0

// Enable seperate display
void DISPLAY_enableCC();

// Setup the display module
void DISPLAY_setup();

// Set all pins LOW
void DISPLAY_reset();

// Set all pins low for both digits
void DISPLAY_clear();

// Set the decimal point active or not
void DISPLAY_setDecimal(int enabled);

// Write an int (0-15) to the display
void DISPLAY_write(int hex);

// Write two ints to the display (0-15)
void DISPLAY_write(int hexLeft, int hexRight);

// Write to display two chars, two dps
void DISPLAY_write(int leftNibble, int rightNibble, int dpLeft, int dpRight);

// Write a custom array of values to the display (LOW or HIGH)
// {A,B,...,F,G}
void DISPLAY_write(int displayState[7] );

// Write a custom array of values to individual segments
// Requires CC Enabled
void DISPLAY_write(int left[7], int right[7]);

// Write a custom value to the left and hex to the right
// Requires CC Enabled
void DISPLAY_write(int customLeft[7], int rightHex);

// Write a seperate value to the right segment, and a hex to the left
// Requires CC Enabled
void DISPLAY_write(int leftHex, int customRight[7]);

#endif // __DISPLAY_H__