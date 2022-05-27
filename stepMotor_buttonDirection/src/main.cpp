#include <Arduino.h>


/*
SW3 horario       HIGH
SW5 anti horario  LOW
SW4 start         HIGH
*/

const int stepPin = 3;
const int dirPin = 4;

int botaoEsquerda = 8; //amarelo
int botaoDireita = 10; //vermelho
int botaoStart = 9; // laranja

void esquerda(){

  digitalWrite(dirPin, HIGH);
  for(int x = 0; x < 20; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(500);

}

void direita(){

  digitalWrite(dirPin, LOW);
  for(int x = 0; x < 20; x++){
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(500);
}

void start(){

  for(int j = 0; j < 25; j++){

    digitalWrite(dirPin, HIGH);
    for(int x = 0; x < 20; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
  }
  delay(1000);
  }

}

bool started = false;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(botaoDireita, INPUT_PULLUP);
  pinMode(botaoEsquerda, INPUT_PULLUP);
  pinMode(botaoStart, INPUT_PULLUP);

  Serial.begin(9600);


  while (started != true){
    if (digitalRead(botaoStart) == LOW){
      started = true;
    }
    if (digitalRead(botaoDireita) == LOW){
      direita();
    }
    if (digitalRead(botaoEsquerda) == LOW){
      esquerda();
    }

  }
  start();
}



void loop() {
  

}
