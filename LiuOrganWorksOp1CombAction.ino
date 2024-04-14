#include <MIDI.h>

/***
 * Liu Organ Works
 * Opus 1
 *
 * Combination action
 */

// Define the MIDI interface
MIDI_CREATE_DEFAULT_INSTANCE();

const int BUTTON_PIN = A15; // the number of the pushbutton pin

int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin

void setup() {
  Serial.begin(31250); // for MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Yeah we started");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH) {
    Serial.println("The state changed from LOW to HIGH");
    MIDI.sendNoteOn(42, 127, 1);
  } else if (lastState == HIGH && currentState == LOW) {
    Serial.println("The state changed from HIGH to LOW");
    MIDI.sendNoteOff(42, 127, 1);
  }

  // save the last state
  lastState = currentState;

  MIDI.read();
}
