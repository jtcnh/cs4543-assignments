// Assignment 6
// Jack Chambers
// Stopwatch


// Includes
#include "Display.h"
#include "Buttons.h"

// constants
const int BTNA = 3;
const int BTNB = 2;

// enums
typedef enum {
  Off,
  Idle,
  Running,
  Stop
} State;


// ISR Exposed Variables
volatile unsigned int ms10 = 0;

volatile bool running = 0;
volatile unsigned int time = 0;

volatile bool flipping = 0;
volatile unsigned int flips = 0;

volatile State timerState = Off;


// Timer Variables
int storedTime = 0;
int timeDisplayed = time;

bool lastA = 0;
bool lastB = 0;

// Private Methods
// 10ms timer1
void TIMER_setup() {
  cli(); // disable interrupts

  TCCR1A = 0; // normal operation
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64
  OCR1A = 2499; // compare match value for 10ms

  TIMSK1 |= (1 << OCIE1A); // enable Timer1 compare interrupt

  sei(); // enable interrupts
}


// Wait for 10ms * length
// 0.010s == 1
// 0.100s == 10
// 0.250s == 25
void TIMER_wait(unsigned int length) {
  unsigned int start = ms10;
  while ((unsigned int)(ms10 - start) < length) {
    // busy wait
  }
}


// Timer ISR
ISR(TIMER1_COMPA_vect) {
  ms10++;

  if ((ms10%10 == 0) && (timerState == Running)) {
    time++;
  }

  if ((ms10%25 == 0) && (timerState == Stop)) {
    flips++;
  }
}


void displayTimeStopwatch() {
  if (time < 100) {
    int ones = time / 10;
    int tenths = time % 10;
    DISPLAY_write(ones, tenths, 1, 0);
  } else {
    int tens = time / 100;
    int ones = (time % 100) / 10;
    DISPLAY_write(tens,ones);
  }
}


// Alternating Display
void displayTimeStopped() {
  // entire form  <10s
  if (timeDisplayed < 100) {
    int ones = timeDisplayed / 10;
    int tenths = timeDisplayed % 10;
    DISPLAY_write(ones, tenths, 1, 0);
    
  // over 10s
  } else {
    if (flips%2==0) {
      int tens = timeDisplayed / 100;
      int ones = (timeDisplayed % 100) / 10;
      DISPLAY_write(tens,ones,0,1);
    } else {
      int tenths = timeDisplayed%10;
      DISPLAY_write(-1, tenths,1,0);
    }
  }
}


// Setup IO
void setup() {
  TIMER_setup();

  DISPLAY_setup();
  DISPLAY_enableCC();

  pinMode(VANDUINO_SW3, INPUT_PULLUP);
  pinMode(VANDUINO_SW2, INPUT_PULLUP);
}


// Hardware Loop
int x = 0;
void loop() {
  bool btnA = digitalRead(VANDUINO_SW3);
  bool btnB = digitalRead(VANDUINO_SW2);

  bool pressedA = (lastA == HIGH) && (btnA == LOW);
  bool pressedB = (lastB == HIGH) && (btnB == LOW);

  DISPLAY_reset();

  // Timer OFF
  if (timerState == Off) {
    // state change conditions
    if (pressedA) {
      timerState = Idle;
    }


    // Timer IDLE
  } else if (timerState == Idle) {
    storedTime = -1;
    time = 0;
    flips = 0;

    DISPLAY_write(-1, 0, 0, 0);

    // state change conditions
    if (pressedA) {
      timerState = Running;
    }


    // Timer RUNNING
  } else if (timerState == Running) {
    displayTimeStopwatch();

    if (pressedB) {
      storedTime = time;
    }

    // state change conditions
    if (pressedA) {
      timerState = Stop;
    }

    // Timer STOPPED
  } else if (timerState == Stop) { 
    if ((btnB == LOW) && (storedTime > -1)) {
      timeDisplayed = storedTime;
    } else {
      timeDisplayed = time;
    }

    displayTimeStopped();

    // state change conditions
    if (pressedA) {
      timerState = Idle;
    }
  }


  lastA = btnA;
  lastB = btnB;
}
