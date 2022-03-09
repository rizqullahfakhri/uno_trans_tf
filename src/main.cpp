#include <Arduino.h>
#include <SPI.h>
#include <RH_ASK.h>

#define LED_rx 6
RH_ASK rf_driver;//edit rx pin = 7

void setup() {
  start:
  Serial.begin(9600);
  Serial.println("TURN ON");
  if(!rf_driver.init()){
    Serial.println("Failed");
    goto start;
  }
  pinMode(LED_rx,OUTPUT);
}

void loop() {
  uint8_t buf=0;
  uint8_t buflen = sizeof(buf);
  if(rf_driver.recv(&buf,&buflen)){
    Serial.println((byte)buf,BIN);
  }
  

    // uint8_t buf[11];
    // uint8_t buflen = sizeof(buf);
    // // Check if received packet is correct size
    // if (rf_driver.recv(buf, &buflen))
    // {
      
    //   // Message received with valid checksum
    //   Serial.print("Message Received: ");
    //   Serial.println((char*)buf);         
    // }
}