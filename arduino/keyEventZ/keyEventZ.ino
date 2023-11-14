#include <Keyboard.h>

const int lineFinderPin = 2;

void printAction() {
    Serial.println("PrintAction");
//   Keyboard.write('z');
//   Keyboard.write(KEY_RETURN);
}

void setup() {
  pinMode(lineFinderPin, INPUT);
  Keyboard.begin();
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(lineFinderPin), printAction, FALLING);
}

void loop() {
    delay(10000);
}
