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
  if (Serial.available() > 0){
    byte e = Serial.read();
    if (e == 'l'){
      ligado = true;
      Serial.println("Sistema Ligado");
    }
    else if (e == 'r'){
      Serial.println("Lendo pir");
      leitura ();
    }
    else if (e == 'd'){
      Serial.println("Deletando arquivo");
      apaga ();
    }
    else if (e == 'g'){
      Serial.println("Testando gravacao");
      grava ();
    }
    else if (e == 'h'){
      ligado = false;
      Serial.println("Sistema Desligado");
    }
    else{
      Serial.println("l para ligaro listema");
      Serial.println("r para ler");
      Serial.println("d para apagar arquivo");
      Serial.println("h para desligar o sistema");
    }
  }
  if(ligado){
    if (digitalRead(pinopir)){  //Com movimento
      Serial.println("Movimento Detectado");
      grava ();
      delay (4000);
    }
  }
}



