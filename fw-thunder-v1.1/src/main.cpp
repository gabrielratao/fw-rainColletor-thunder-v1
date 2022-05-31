#include <Arduino.h>
#include <SPI.h>

//PINOS DO ARUDINO PARA O MOTOR 
const int stepPin = 3;
const int dirPin = 4;

//RTC configurações
#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA

RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231


/*BOTÕES (SW's é a numeração dos botões)
SW3 horario       HIGH
SW5 anti horario  LOW
SW4 start         HIGH
*/
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

//int hora, int minuto, 
void pausa(int cnt){
  unsigned long time;
  int intervalo = 5;
  time = millis();

  while((time/1000) <= intervalo*cnt){
    
    //Serial.print("Dentro da pausa por: ");
    //Serial.print(time);
    //Serial.println(" segundos");
    time = millis();
  }


/*
  DateTime now = rtc.now();
  int horaInicial = now.hour();
  int minutoInicial = now.minute();
  int segundoInicial = now.second();
  Serial.print("segundoInicial: ");
  Serial.println(segundoInicial);

  
  if(50 <= segundoInicial <= 59){
    int segPosIntervalo = (segundoInicial - 10) + pausaSegundo;

  }
  else{
    int segPosIntervalo = segundoInicial + pausaSegundo;
  }
  */
  /*
  while(intervalo != true){
    DateTime now = rtc.now();
    int horaAtual = now.hour();
    int minutoAtual = now.minute();
    int segundoAtual = now.second();
    Serial.print("segundoAtual: ");
    Serial.println(segundoAtual);
    
    
    
    
    if(segundoAtual >= (segPosIntervalo)){
      intervalo = true;
    }
    
  }
  */

    
  
}

void start(){
  Serial.println("Inciando Sistema");
  Serial.println("-=-=-=-=-=-=-=-=-=-=-=-==-=-==-=-=");
  Serial.println("Frasco: 1");
  pausa(1);
  
  

  for(int j = 1; j < 26; j++){

    digitalWrite(dirPin, HIGH);
    for(int x = 0; x < 20; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
  }

  //intervalo entre os frascos
  //delay(1000);
  if(j > 1){
    Serial.print("Frasco: ");
    Serial.println(j);
    pausa(j);
    
  }
  
  
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
  rtc.begin();


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
