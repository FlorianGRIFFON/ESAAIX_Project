const int ledPin = 13;       // LED connected to digital pin 13
const int knockSensor = A0;  // the piezo is connected to analog pin 0
const int threshold = 35;   // threshold value to decide when the detected sound is a knock or not
const int outputPin = 3;

// these variables will change:
int sensorReading = 0;  // variable to store the value read from the sensor pin

void setup() {
  Serial.begin(115200);       // use the serial port
  pinMode(outputPin, OUTPUT);
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = analogRead(knockSensor);

  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // send the string "Knock!" back to the computer, followed by newline
    Serial.print("Knock: ");
    Serial.println(sensorReading);
    digitalWrite(outputPin, HIGH);
    delay(100);
    digitalWrite(outputPin, LOW);
  }
  delay(10);  // delay to avoid overloading the serial port buffer
}