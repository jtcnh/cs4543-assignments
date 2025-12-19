// Jack Chambers
// Display.h
// 9/24/2025
// Contains header info for 7seg display on vanduino


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

// Display Pullup Resistors
#define DISPLAY_CC1 9 // Shares with SW1
#define DISPLAY_CC2 8 // Shares with SW0

void DISPLAY_enableCC();
void DISPLAY_setup();
void DISPLAY_reset();
void DISPLAY_clear();
void DISPLAY_setDecimal();
void DISPLAY_write(int hex);
void DISPLAY_writeSeperate(int hexLeft, int hexRight);

#endif // __DISPLAY_H__