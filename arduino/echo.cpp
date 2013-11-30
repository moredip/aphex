#include "Arduino.h"

#define SHORT_DELAY (300)
#define LONG_DELAY (600)

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("waiting...");
    digitalWrite(13,HIGH); delay(LONG_DELAY); digitalWrite(13,LOW); delay(SHORT_DELAY);
  }
}

void setup()
{
  pinMode(13, OUTPUT);   // digital sensor is on digital pin 2
  
  Serial.begin(9600);

  establishContact();  // send a byte to establish contact until receiver responds 
}

void loop() {
  Serial.write( ">" );
  while (Serial.available() <= 0) {
    digitalWrite(13,HIGH); delay(SHORT_DELAY); digitalWrite(13,LOW); delay(SHORT_DELAY);
  }
  
  char input[1025];
  int bytesRead = Serial.readBytesUntil( '\n', input, 1024 );
  if( bytesRead ){
    Serial.write( "\necho:  " );
    Serial.write( (byte *)input, bytesRead );
    Serial.write( "\n" );
  }
}

//// standard Arduino main.cpp, copied from https://github.com/arduino/Arduino/blob/master/hardware/arduino/cores/arduino/main.cpp
//int main(void)
//{
  //init();

  //setup();
    
  //for (;;) {
    //loop();
    //if (serialEventRun) serialEventRun();
  //}
        
  //return 0;
//}
