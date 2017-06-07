#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial minha(2, 3); 

void setup(){
  Serial.begin(9600);
  minha.begin(19200); //AT+RST
}

void loop(){ 
  if (Serial.available() > 0) {
    delay(2);
    char ch = Serial.read();
    minha.print(ch);
  }
  if (minha.available() > 0) {
    delay(2);
    char ch = minha.read();
    Serial.print(ch);
  }
}
