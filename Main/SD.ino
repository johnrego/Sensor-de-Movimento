void leitura (){
  arquivo = SD.open("pir.txt");
  if (arquivo){
    while (arquivo.available()){
      Serial.write(arquivo.read());
    }
  arquivo.close();
  Serial.println("Termino da leitura");
  }
  else{
    Serial.println("Erro na leitura");
  }
}

void apaga (){
  SD.remove ("pir.txt");
  if (!SD.exists ("pir.txt") ){
    Serial.println ("Arquivo apagado com sucesso");
  }
}

void grava (){
  arquivo = SD.open("pir.txt", FILE_WRITE);
  if (arquivo) {
    Serial.println("Iniciando gravacao");
    DateTime now = rtc.now();
    arquivo.print("Movimento: ");
    if(now.hour() > 9){
      arquivo.print(now.hour(), DEC);
    }
    else{
      arquivo.print("0");
      arquivo.print(now.hour(), DEC);
    }
    arquivo.print(':');
    if(now.minute() > 9){
      arquivo.print(now.minute(), DEC);
    }
    else{
      arquivo.print("0");
      arquivo.print(now.minute(), DEC);
    }
    arquivo.print(':');
    if(now.second() > 9){
      arquivo.print(now.second(), DEC);
    }
    else{
      arquivo.print("0");
      arquivo.print(now.second(), DEC);
    }
    arquivo.print(' ');
    if(now.day() > 9){
      arquivo.print(now.day(), DEC);
    }
    else{
      arquivo.print("0");
      arquivo.print(now.day(), DEC);
    }
    arquivo.print('/');
    if(now.month() > 9){
      arquivo.print(now.month(), DEC);
    }
    else{
      arquivo.print("0");
      arquivo.print(now.month(), DEC);
    }
    arquivo.print('/');
    arquivo.print(now.year(), DEC);
    arquivo.println();
    arquivo.close();  
    Serial.println("Fim da gravacao");
  }
  else{
    Serial.println("Erro na gravacao");
  }
}

