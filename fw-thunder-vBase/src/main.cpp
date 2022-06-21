#include <Arduino.h>

//PINOS DO ARUDINO PARA O MOTOR 
const int stepPin = 3;
const int dirPin = 4;

//BOTÃO 
int botaoStart = 9; // laranja SW4
int botaoEsquerda = 8; //amarelo
int botaoDireita = 10; //vermelho

void start(){

  for(int j = 1; j <= 25; j++){

    digitalWrite(dirPin, HIGH);
    for(int x = 0; x < 8; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
    }
    delay(2000); //INTERVALO
  }
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


bool started = false;

void setup() {

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(botaoStart, INPUT_PULLUP);
  

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