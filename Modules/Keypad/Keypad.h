// Jack Chambers
// Keypad.h
// Keypad Control Header
// 11/18/2025

/*

!! Vanduino Conflicts !!
	Serial (D0, D1)
	Display (D0 - D7)

*/

#ifndef __KEYPAD_H__
#define __KEYPAD_H__

// define row pins
#define KEYPAD_ROW0 7
#define KEYPAD_ROW1 0
#define KEYPAD_ROW2 1
#define KEYPAD_ROW3 3

// define col pins
#define KEYPAD_COL0 2
#define KEYPAD_COL1 4
#define KEYPAD_COL2 5
#define KEYPAD_COL3 6

const int KEYPAD_ROW[] = {KEYPAD_ROW0, KEYPAD_ROW1, KEYPAD_ROW2, KEYPAD_ROW3};
const int KEYPAD_COL[] = {KEYPAD_COL0, KEYPAD_COL1, KEYPAD_COL2, KEYPAD_COL3};

const char KEYPAD_MAP[4][4] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};

void KEYPAD_setup();
char KEYPAD_scanRaw();
char KEYPAD_scanSteady();

#endif // __KEYPAD_H__