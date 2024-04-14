// #include <Control_Surface.h>

#include <MIDI.h>

const int NUM_BUTTONS = 55;
const int ALL_BUTTON_PINS[NUM_BUTTONS] = {
  A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, // Generals
  22, 23, 24, 25, 26, 27, // Man III divisionals
  7, 6, 5, 4, 3, 2, // Man II divisionals
  13, 12, 11, 10, 9, 8, // Man I divisionals
  37, 39, // Man III sequencers
  36, 38, // Man II sequencers
  15, 16, // Man I sequencers
  35, 41, // Man III couplers
  34, 40, 42, // Man II couplers
  14, 17, A15, // Man I couplers
  51, 53, // Man III assignables
  50, 52, // Man II assignables
  32, 33, // Man I assignables
  18, // Setter
  19 // General cancel
};
// NB: As we are using GND and internal pull-ups then the "released" state of the button is "1".
bool buttonStates[NUM_BUTTONS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};



/***
 * Liu Organ Works
 * Opus 1
 *
 * Combination action
 */

// Define the MIDI interface
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(31250); // for MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(ALL_BUTTON_PINS[i], INPUT_PULLUP);
  }

  Serial.println("Yeah we started");
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    int pinNumber = ALL_BUTTON_PINS[i];
    bool currentState = digitalRead(pinNumber);
    bool lastState = buttonStates[i];
    
    if (currentState != lastState) {
      buttonStates[i] = currentState;

      if (currentState == HIGH) {
        Serial.print("Button released: ");
        Serial.println(pinNumber);
        MIDI.sendNoteOff(pinNumber, 127, 1);
      } else {
        Serial.print("Button pressed: ");
        Serial.println(pinNumber);
        MIDI.sendNoteOn(pinNumber, 127, 1);
      }
    }
  }

  MIDI.read();
}
