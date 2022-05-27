#include <Arduino.h>

const int stepPin = 3;
const int dirPin = 4;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  
  
}

void loop() {

  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < 200; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(2000);

  digitalWrite(dirPin, LOW);
  for(int x = 0; x < 200; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(2000);

  
}