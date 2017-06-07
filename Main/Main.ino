#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"
#include "SoftwareSerial.h"

File arquivo;
RTC_DS1307 rtc;
SoftwareSerial esp8266(2, 3);

String enviaEsp(String command, const int timeout);
void enviaWeb(String msg);
void limpa();
void grava();

byte pir = 8;

void setup(){
  rtc.begin();
  esp8266.begin(19200);
  Serial.begin(9600);
  if (!SD.begin(9)) {
    Serial.println("Erro no cartao");
  }
  pinMode(pir, INPUT);
  /* Para se conectar consultar o arquivo de conexão */
  enviaEsp("AT+CIPMUX=1\r\n", 1000);
  enviaEsp("AT+CIPSERVER=1,80\r\n", 1000);
}

void loop(){
  if (digitalRead(pir)){
    Serial.println("Movimento Detectado");
    grava ();
    delay (4000);
  }
  else if (esp8266.available()){
    if (esp8266.find("+IPD,")){
      delay(100);
      if(esp8266.find("limpa")){
        limpa();
        enviaWeb("O Arquivo sera limpo.");
      }
      else{
        arquivo = SD.open("pir.txt");
        if (arquivo){
          String linha;
          while (arquivo.available()){
            char ch = arquivo.read();
            if (ch == '\n'){
              enviaWeb(linha);
              linha = "";
            }
            else{
              linha += ch;
            }
          }
          arquivo.close();
          enviaWeb("Fim");
        }
        else {
          enviaWeb("Erro ao acessar o cartao");
        }
      }
    }   
  }
}

void enviaWeb(String msg){
  msg += "\r\n";
  String cipSend = "AT+CIPSEND=0,";
  cipSend += msg.length();
  cipSend += "\r\n";
  enviaEsp(cipSend, 1000);
  enviaEsp(msg, 1000);
}

String enviaEsp(String command, const int timeout){
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ((time + timeout) > millis()){
    while (esp8266.available()){
      char c = esp8266.read();
      response += c;
    }
  }
  Serial.print(response);
  return response;
}

