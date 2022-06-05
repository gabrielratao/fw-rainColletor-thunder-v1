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

//SHT20 
#include "DFRobot_SHT20.h"
DFRobot_SHT20 sht20;

//cartão SD
#include <SD.h>

const int chipSelect = 7;
File dataFile;



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
  dataFile = SD.open("chuva5.txt", FILE_WRITE);
  dataFile.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
  dataFile.println("recipiente, data, horário, umidade, temperatura");
  dataFile.println("Temperatura: °C e Umidade % relativa\n(ambos valores são médias do intervalo)");

  //inicio dos passos

  for(int j = 1; j <= 25; j++){
    Serial.print("Frasco: ");
    Serial.println(j);
    Serial.println("Pausa");

    dataFile.print(j); // grava o frasco no cartão sd
    dataFile.print(", ");
    DateTime now = rtc.now();// data e hora
    dataFile.print(now.day(), DEC); 
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/'); 
    dataFile.print(now.year(), DEC); 
    dataFile.print(", ");
  
    dataFile.print(now.hour(), DEC); 
    dataFile.print(':');
    dataFile.print(now.minute(), DEC); 
    dataFile.print(':');
    dataFile.print(now.second(), DEC); 
    dataFile.print(", ");

    //intervalo entre os frascos
    //programa começa parado, fica no itervalo calculando a média de temp e umid,
    //ai depois ele dá um passo para o próximo frasco
    unsigned long time;
    int intervalo = 5;
    time = millis();
    int cntTemp = 0;
    int cntUmid = 0;
    float tempMedia = 0;
    float umidMedia = 0;
    float somaTemp = 0;
    float somaUmid = 0;

    if (j == 1){
      delay(1000);
    }
    while((time/1000) <= intervalo*j){
      //medição de temperatura e umidade 
      float umd = sht20.readHumidity();
      float temp = sht20.readTemperature();

      cntTemp += 1;
      cntUmid += 1;
      somaTemp += temp;
      somaUmid += umd;

      time = millis();

  }
    tempMedia = (somaTemp / cntTemp);
    umidMedia = (somaUmid / cntUmid);

    dataFile.print(umidMedia);
    dataFile.print(", ");
    dataFile.println(tempMedia);
    
    


    digitalWrite(dirPin, HIGH);
    for(int x = 0; x < 20; x++){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(1000);
  }
    Serial.println("Prox frasco");
  
  }
  dataFile.close();
  Serial.print("FIM DO PROGRAMA");
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
  sht20.initSHT20();
  SD.begin(chipSelect);


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
