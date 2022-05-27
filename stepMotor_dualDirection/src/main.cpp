#include <Arduino.h>

const int stepPin = 3;
const int dirPin = 4;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {

  Serial.println("Direção horario");
  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < 200; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(2000);

  Serial.println("Direção Anti horario");
  digitalWrite(dirPin, LOW);
  for(int x = 0; x < 200; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
  delay(2000);

  
}