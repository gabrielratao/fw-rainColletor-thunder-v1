#include <Arduino.h>

int led = 13;
int botaoVermelho = 8;

void pisca(){

  for(int i = 0; i < 5; i++){
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  }

}

void setup() {
  pinMode(led, OUTPUT);
  pinMode(botaoVermelho, INPUT_PULLUP);
  
}

void loop() {
  if (digitalRead(botaoVermelho) == LOW){
    pisca();

  }
}
