#ifndef __BUTTONS_H__
#define __BUTTONS_H__

const int BUTTON_IDX[4] = {8, 9, 10, 11};
const int DEBOUNCE_TIME = 10;

// Button Setup
// Idx => [0,3]
// Note CC for Display uses idx 0,1
void BUTTON_setup(int idx);


// Debounce Button
// ButtonIdx => [0,3]
int BUTTON_db(int buttonIdx);

// Debounce Button
// ButtonIdx => [0,3]
// DebounceTime => ms
int BUTTON_db(int buttonIdx, int debounceTime);

#endif // __BUTTONS_H__