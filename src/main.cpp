#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#define LED_rx 6

int i, good, k;
byte data_in;
File myfile;

void data_incoming(){
    
    digitalWrite(LED_rx,HIGH);
    for(i=0; i<100; i++){
      delayMicroseconds(20);
      good=1;
      if(digitalRead(3)==LOW){
      good=0;
      i=100;
      }
    }//for
      
    if(good==1){
    detachInterrupt(1);
    while(1){
      if(digitalRead(3)==LOW){
        delayMicroseconds(750);

        for(i=0; i<8; i++){
          if(digitalRead(3)==HIGH)
          bitWrite(data_in, i, 1);
          else
          bitWrite(data_in, i, 0);
          delayMicroseconds(1000);
        }//for
        if(data_in=='#'){
        Serial.println("");
        myfile.println("");
        }
        else{
        Serial.print(data_in);
        Serial.print(".");
        myfile.print(data_in);
        myfile.print(".");
        }

       break;//secondtwhile
      }//low kickoff
      
    }//second while
    
    }//good check
  digitalWrite(LED_rx,LOW);
  if(digitalRead(7)==LOW){
    myfile.close();
    while(1){
      digitalWrite(LED_rx,HIGH);
    }
  }
  attachInterrupt(1,data_incoming,RISING);
  
  
  
}//routine

void setup() {
  start:
  attachInterrupt(1,data_incoming,RISING);
  Serial.begin(115200);
  Serial.println("TURN ON");
  pinMode(LED_rx,OUTPUT);
  pinMode(3, INPUT);
  pinMode(7, INPUT_PULLUP);
  if (!SD.begin(10)){
    goto start;
  }
  myfile = SD.open("text.txt",FILE_WRITE);
  myfile.println("START");
}

void loop() {

}