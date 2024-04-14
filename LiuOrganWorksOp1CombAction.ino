/***
 * Liu Organ Works
 * Opus 1
 *
 * Combination action
 */

const int BUTTON_PIN = A15; // the number of the pushbutton pin

int lastState = HIGH; // the previous state from the input pin
int currentState;    // the current reading from the input pin

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Yeah we started");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH) {
    Serial.println("The state changed from LOW to HIGH");
  } else if (lastState == HIGH && currentState == LOW) {
    Serial.println("The state changed from HIGH to LOW");
  }

  // save the last state
  lastState = currentState;
}
