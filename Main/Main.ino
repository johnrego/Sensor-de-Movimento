#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

File arquivo;
RTC_DS1307 rtc;

byte pinopir = 8;
boolean ligado = false;

void apaga();
void grava();
void leitura();

void setup() {
  Serial.begin(9600);
  rtc.begin();
  //rtc.adjust(DateTime(2017, 6, 8, 21, 59, 0));
  pinMode(pinopir, INPUT);
  if (!SD.begin(9)) {
    Serial.println("Falha no Cartao");
    return;
  }
  arquivo = SD.open("pir.txt", FILE_WRITE);
  if (arquivo) {
    Serial.println("Arquivo OK");
  }
  else{
    Serial.println("Erro no Arquivo");
  }
  arquivo.close();
}

void loop() {
  if (Serial.available()){
    byte e = Serial.read();
    switch (e) {
      case 'a':
        Serial.println("Deletando arquivo");
        apaga ();
      break;
      case 'd':
        ligado = false;
        Serial.println("Sistema Desligado");
      break;
      case 'l':
        ligado = true;
        Serial.println("Sistema Ligado");
      break;
      case 'r':
        Serial.println("Lendo pir");
        leitura ();
      break;
      case 's':
        Serial.print("Status: ");
        if (ligado){
          Serial.println("ligado");
        }
        else{
          Serial.println("desligado");
        }
      break;
      default:
        Serial.println("a para apagar");
        Serial.println("d para desligar o sistema");
        Serial.println("l para ligaro sistema");
        Serial.println("r para ler");
        Serial.println("s para status");
      break;
    }
  }
  else{
    if(ligado){
      if (digitalRead(pinopir)){  //Com movimento
        Serial.println("Movimento Detectado");
        grava ();
        delay (4000);
      }
    }
  }
}



