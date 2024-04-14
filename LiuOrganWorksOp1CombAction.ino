/***
 * Liu Organ Works
 * Opus 1
 *
 * Combination action
 */

const int NUM_BUTTONS = 68;
// NB: As we are using GND and internal pull-ups then the "released" state of the button is "1".
bool buttonStates[NUM_BUTTONS] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


void setup() {
  Serial.begin(115200); // needs to be 31250 for MIDI, 115200 for Hairless

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(i, INPUT_PULLUP);
  }

  // Serial.println("Yeah we started");
}

void loop() {

  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool currentState = digitalRead(i);
    bool lastState = buttonStates[i];
    
    if (currentState != lastState) {
      buttonStates[i] = currentState;

      if (currentState == HIGH) {
        noteOn(0x80 /* note off */, i, 127);
      } else {
        noteOn(0x90 /* note on */, i, 127);
      }
    }
  }

  // midi.update();
  delay(10);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}