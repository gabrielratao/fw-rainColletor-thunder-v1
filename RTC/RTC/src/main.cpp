#include <Arduino.h>

#include <SPI.h>
//sensor temperatura
#include "DHT.h"

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

//RTC
#include <Wire.h> //INCLUSÃO DA BIBLIOTECA
#include "RTClib.h" //INCLUSÃO DA BIBLIOTECA

RTC_DS3231 rtc; //OBJETO DO TIPO RTC_DS3231

//char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
 

void setup () {
  
  Serial.begin(9600);
  Serial.println("Monitoramento de Temperatura/Umidade com RTC");
  Serial.println("Data, Horário, Umidade, Temperatura");
  
  dht.begin();
  rtc.begin();

  
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
  //rtc.adjust(DateTime(2022, 3, 28, 12, 46, 25)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
}

float media_temp;

float media_umd;


int intervalo = 1;
int minuto_pos_intervalo;
int minuto_atual;

int horario_inicial;
bool pausa = true;

void loop() {
  
    
   DateTime now = rtc.now();
   horario_inicial = now.minute();
   minuto_pos_intervalo = horario_inicial + intervalo;
   
   pausa = true;

   float cnt_temp = 0;
   float soma_temp = 0;
   
   float cnt_umd = 0;
   float soma_umd = 0;
   
   while(pausa == true){
    
     float h = dht.readHumidity();
     float t = dht.readTemperature();
     
     // testa se retorno é valido, caso contrário algo está errado.
     if (isnan(t) || isnan(h)) {
      Serial.println("Falha na leitura do Sensor");
      } 
      
     else{ 
      
       DateTime now = rtc.now();
       minuto_atual = now.minute();

       //fazer as medias dos valor;es de temperatura
       
              
       cnt_temp = cnt_temp + 1;
       soma_temp = soma_temp + t;

   
       cnt_umd = cnt_umd + 1;
       soma_umd = soma_umd + h;
        
        }
     
     if (minuto_atual >= minuto_pos_intervalo) {
      Serial.print("pausa do invervalo ok");
      pausa = false;
      
      media_temp = (soma_temp / cnt_temp);
      media_umd = (soma_umd / cnt_umd);
      DateTime now = rtc.now(); //CHAMADA DE FUNÇÃO
    
      //Serial.print("Data: "); //IMPRIME O TEXTO NO MONITOR SERIAL
      Serial.println();
      Serial.print(now.day(), DEC); //IMPRIME NO MONITOR SERIAL O DIA
      Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
      Serial.print(now.month(), DEC); //IMPRIME NO MONITOR SERIAL O MÊS
      Serial.print('/'); //IMPRIME O CARACTERE NO MONITOR SERIAL
      Serial.print(now.year(), DEC); //IMPRIME NO MONITOR SERIAL O ANO
      
      Serial.print(", "); 
      Serial.print(now.hour(), DEC); //IMPRIME NO MONITOR SERIAL A HORA
      Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
      Serial.print(now.minute(), DEC); //IMPRIME NO MONITOR SERIAL OS MINUTOS
      Serial.print(':'); //IMPRIME O CARACTERE NO MONITOR SERIAL
      Serial.print(now.second(), DEC); //IMPRIME NO MONITOR SERIAL OS SEGUNDOS

      Serial.print(", ");
      Serial.print(media_temp);
      Serial.print("°C");
      Serial.print(", ");
      Serial.print(media_umd);
      Serial.println("%");
      
      }
   }
   

  
}