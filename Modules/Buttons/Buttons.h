#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "Vanduino.h"

const int BUTTON_IDX[4] = {VANDUINO_SW0, VANDUINO_SW1, VANDUINO_SW2, VANDUINO_SW3};

int BUTTON_db(int buttonIdx);
int BUTTON_db(int buttonIdx, int debounceTime);
void BUTTON_setup(int buttonIdx);

#endif // __BUTTONS_H__