void limpa(){
  SD.remove ("pir.txt");
}

void grava(){
  arquivo = SD.open("pir.txt", FILE_WRITE);
  if (arquivo) {
    DateTime now = rtc.now();
    arquivo.print("Movimento: ");
    if(now.hour() > 9){
      arquivo.print(now.hour());
    }
    else{
      arquivo.print('0');
      arquivo.print(now.hour());
    }
    arquivo.print(':');
    if(now.minute() > 9){
      arquivo.print(now.minute());
    }
    else{
      arquivo.print('0');
      arquivo.print(now.minute());
    }
    arquivo.print(':');
    if(now.second() > 9){
      arquivo.print(now.second());
    }
    else{
      arquivo.print('0');
      arquivo.print(now.second());
    }
    arquivo.print(' ');
    if(now.day() > 9){
      arquivo.print(now.day());
    }
    else{
      arquivo.print('0');
      arquivo.print(now.day());
    }
    arquivo.print('/');
    if(now.month() > 9){
      arquivo.print(now.month());
    }
    else{
      arquivo.print('0');
      arquivo.print(now.month());
    }
    arquivo.print('/');
    arquivo.print(now.year());
    arquivo.println();
    arquivo.close();  
  }
}
