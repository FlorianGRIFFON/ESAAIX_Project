#include "Keyboard.h"

int jumpPin = 6; 
int leftPin = A1;
int rightPin = 3;
int leftState;
int rightState;
int lastLeftState;
int lastRightState;

int sameStateCount = 0;
int doingLeft = 0;
int doingRight = 0;

int potState;
int potPin = A0;
 
int lastPotState;

void jumpAction()
{
    Serial.println("PrintActionSpace");
    Keyboard.write(' ');
}

void potAction()
{
    Serial.println("PrintActionW");
    Keyboard.write('z');
}

void leftAction()
{
    Serial.println("PrintActionQ");
    Keyboard.write('a');
}

void rightAction()
{
    Serial.println("PrintActionD");
    Keyboard.write('d');
}

void setup() {
  // Run once:
  Serial.begin(115200);
  pinMode (jumpPin, INPUT_PULLUP);
  pinMode (leftPin, INPUT);
  pinMode (rightPin, INPUT);
  
  Keyboard.begin();
}

void loop() {
    // Run repeatedlyotState
    potState = analogRead (potPin);
    int lSt = analogRead (leftPin);
    rightState = digitalRead(rightPin);
    if (lSt > 700)
        leftState = 0;
    else
        leftState = 1;
    
    if (sameStateCount >= 30) {
        doingLeft = 0;
        doingRight = 0;
        if (leftState != lastLeftState) {
            doingLeft = 1;
        } else if (rightState != lastRightState) {
            doingRight = 1;
        }
    }

    if (leftState == lastLeftState && rightState == lastRightState) {
        sameStateCount++;
    } else {
        sameStateCount = 0;
        Serial.println("PrintActionY");
        Keyboard.write('y');
    }

    if (doingLeft == 1)
        leftAction();
    if (doingRight == 1)
        rightAction();

    // Serial.print("sameStateCount: ");
    // if (sameStateCount == 6) {
    //     Serial.println(sameStateCount);
    // }

    // leftState = digitalRead(leftPin);

    // Serial.print("potState: ");
    // Serial.println(potState);
    // Serial.print("lastPotState: ");
    // Serial.println(lastPotState);

    // Serial.print("leftState: ");
    // Serial.println(leftState);
    // Serial.print("lastLeftState: ");
    // Serial.println(lastLeftState);

    // Serial.print("rightState: ");
    // Serial.println(rightState);
    // Serial.print("lastRightState: ");
    // Serial.println(lastRightState);

  
    if (digitalRead(jumpPin) == LOW) {
        jumpAction();
    }
    
    if ((potState < lastPotState - 5) || (potState > lastPotState + 5)){
        potAction();
    }

    lastPotState = potState;
    lastLeftState = leftState;
    lastRightState = rightState;

}