#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package {
  int x = 0;
  int y = 0;
  char  text[300] = "Radio 1";
};


typedef struct package Package;
Package dataRecieve;
Package dataTransmit;

void setup() {
  Serial.begin(115200);
  
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() {
  if ( myRadio.available()) {
    while (myRadio.available()){
      myRadio.read( &dataRecieve, sizeof(dataRecieve) );
    }
    Serial.println(dataRecieve.x);
    Serial.println(dataRecieve.y);
    Serial.println(dataRecieve.text);
    Serial.print("\n");
  }

//  myRadio.stopListening();
//  Serial.println("Transmit: ");    
//  Serial.println(dataTransmit.text);
//  Serial.print("\n");
//  myRadio.openWritingPipe(addresses[0]);
//  myRadio.write(&dataTransmit, sizeof(dataTransmit));
//  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}
