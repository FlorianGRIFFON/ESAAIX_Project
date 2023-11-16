#include <Keyboard.h>

// Pins used
const int lineFinderPinA = 2;
const int lineFinderPinB = 7;
const int buttonPin = 3;

// Debounce delay
const unsigned long debounceDelay = 3000;

// Variables to store the last time the input pin was toggled
unsigned long lastDebounceTimeA = 0;
unsigned long lastDebounceTimeB = 0;
unsigned long lastDebounceTimeButton = 0;

// Flags to indicate whether the ball is in the cup
bool ballInCupA = false;
bool ballInCupB = false;

// Buttons states
bool buttonState = HIGH;
bool lastButtonState = HIGH;

// Print actions function
void printActionA() {
  if ((millis() - lastDebounceTimeA) > debounceDelay) {
    Serial.println("PrintActionA");
    Keyboard.write('q');
    Keyboard.write(KEY_RETURN);
    ballInCupA = true;
    lastDebounceTimeA = millis();
  }
}

void printActionB() {
  if ((millis() - lastDebounceTimeB) > debounceDelay) {
    Serial.println("PrintActionB");
    Keyboard.write('b');
    Keyboard.write(KEY_RETURN);
    ballInCupB = true;
    lastDebounceTimeB = millis();
  }
}

void printActionE() {
  Serial.println("PrintActionE");
  Keyboard.write('e');
  Keyboard.write(KEY_RETURN);
}

void handleButtonInterrupt() {
  buttonState = digitalRead(buttonPin);

  if ((millis() - lastDebounceTimeButton) > debounceDelay) {
    if (buttonState != lastButtonState) {
      if (buttonState == LOW) {
        printActionE();
      }
      lastButtonState = buttonState;
      lastDebounceTimeButton = millis();
    }
  }
}

// Call Interrupt | Setup
void setup() {
  pinMode(lineFinderPinA, INPUT);
  pinMode(lineFinderPinB, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(lineFinderPinA), printActionA, FALLING);
  attachInterrupt(digitalPinToInterrupt(lineFinderPinB), printActionB, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonInterrupt, FALLING);
  Keyboard.begin();
  Serial.begin(115200);
}

// Check if the ball is in cup A or B | Reset flag once actions are performed
void loop() {
  if (ballInCupA) {
    ballInCupA = false;
  }
  
  if (ballInCupB) {
    ballInCupB = false;
  }
  
  delay(100);
}
