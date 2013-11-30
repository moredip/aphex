#include "Arduino.h"

#include "rgb/serial_stream.h"
#include "rgb/task.h"
#include "rgb/led_strober_task.h"
#include "rgb/fader_task.h"
#include "rgb/blinker_task.h"
#include "rgb/watchdog.h"

#define WATCHDOG_TIMEOUT (120000) //2 minutes


//Light light(9,10,11);
Light light(3,5,6);
Color purple("ff00ff");
Color off("000000");

FaderTask awaitingOrders = FaderTask(light,purple,off,800);
FaderTask fader = FaderTask(light,Color("ff0000"),Color("00ff10"),1000);
LedStroberTask stroberTask = LedStroberTask(13,1000.0);

Watchdog watchdog = Watchdog( &awaitingOrders, WATCHDOG_TIMEOUT );

void establishContact() {
  while (!Serial) {
    // wait   for serial port to connect. Needed for Leonardo only
    digitalWrite(13,HIGH); delay(100); digitalWrite(13,LOW); delay(1000);
  }

  while (Serial.available() <= 0) {
    Serial.println("waiting...");
    digitalWrite(13,HIGH); delay(200); digitalWrite(13,LOW); delay(50);
  }
}


void setup() {                
  light.setup();
  
  Serial.begin(57600);

  establishContact();
}

const Color readRGB(){
  char rawBytes[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
  Serial.readBytes( rawBytes, 6 );
  return Color( rawBytes );
}

const int readDuration(){
  return Serial.parseInt();
}


void readInput(){
  const Color startingColor = readRGB();
  const Color endingColor = readRGB();
  const int duration = readDuration();
}

void loop() {
  awaitingOrders.slice();
  watchdog.slice();
  stroberTask.slice();
  
  //fader.slice();

  if( !Serial.available() ) return;

  awaitingOrders.disable();
  watchdog.assuage();

  readInput();
 
  const Color color = readRGB();
  color.describe( Serial ); Serial << '\n';
  light.displayColor( color );
}



// standard Arduino main.cpp, copied from https://github.com/arduino/Arduino/blob/master/hardware/arduino/cores/arduino/main.cpp
int main(void)
{
  init();

  setup();
    
  for (;;) {
    loop();
    if (serialEventRun) serialEventRun();
  }
        
  return 0;
}
