#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#define LED_rx 6
unsigned long previousMillis = 0;
int i, good, k, timeMil;
uint16_t data_in =0;
File myfile;

void printTime(){
  unsigned long currentmillis = millis();
  timeMil = currentmillis - previousMillis;
  myfile.print(" ");
  myfile.print(timeMil);
  myfile.print(" ");
  previousMillis = currentmillis;
}

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

        for(i=0; i<9; i++){
          if(digitalRead(3)==HIGH){
          bitWrite(data_in, i, 1);
          myfile.print("1");
          }
          else{
          bitWrite(data_in, i, 0);
          myfile.print("0");
          }
          delayMicroseconds(1000);
        }//for
        // if(data_in=='}'){
        //   Serial.println("");
        //   myfile.println("");
        // }
        // else{
        //   printTime();
        //   Serial.print(data_in);
        //   Serial.print(".");
        //   myfile.print(data_in);
        //   myfile.print(".");
        // }
        // bitWrite(data_in,11,1);
  
        if(data_in>512){
          data_in=512;
        }
        Serial.println(data_in);
        Serial.println(data_in,BIN);
        float temp = (float)data_in/10;
        printTime();
        myfile.print(temp);
        myfile.print(" ");
        myfile.println(data_in);
        Serial.println(temp);

       break;//secondtwhile
      }//low kickoff
      
    }//second while
    
    }//good check
  digitalWrite(LED_rx,LOW);
  if(digitalRead(7)==LOW){
    myfile.println("Stop");
    myfile.close();
    while(1){
      digitalWrite(LED_rx,HIGH);
    }
  }
  attachInterrupt(1,data_incoming,RISING);
  
  
  
}//routine

void setup() {
  start:
  Serial.begin(115200);
  Serial.println("TURN ON");
  pinMode(LED_rx,OUTPUT);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(LED_rx,LOW);
  if (!SD.begin(10)){
    Serial.println("SD FAIL");
    goto start;
  }
  // if (digitalRead(7)!=LOW){
  //   digitalWrite(LED_rx,HIGH);
  //   delay(1000);
  //   goto start;
  // }
  myfile = SD.open("UJICOBA.txt",FILE_WRITE);
  myfile.println("START");
  Serial.println("Start");
  attachInterrupt(1,data_incoming,RISING);
  pinMode(3, INPUT);
}

void loop() {

}