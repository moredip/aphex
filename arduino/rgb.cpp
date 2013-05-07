#include "Arduino.h"

#include "rgb/serial_stream.h"
#include "rgb/fader_task.h"
#include "rgb/blinker_task.h"
#include "rgb/watchdog.h"

#define WATCHDOG_TIMEOUT (10000)


Light light(9,10,11);
Color purple("ffff00");

BlinkerTask awaitingOrders = BlinkerTask(light,purple,800);
FaderTask fader = FaderTask(light,Color("ff0000"),Color("00ff10"),1000);

Watchdog watchdog = Watchdog( &awaitingOrders, WATCHDOG_TIMEOUT );

void setup() {                
  light.setup();
  
  Serial.begin(57600);
}

const Color readRGB(){
  char rawBytes[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
  Serial.readBytes( rawBytes, 6 );
  Serial << "received " << rawBytes << '\n';
  return Color( rawBytes );
}

void loop() {
  //awaitingOrders.slice();
  //watchdog.slice();
  
  fader.slice();

  if( !Serial.available() ) return;

  awaitingOrders.disable();
  watchdog.assuage();
 
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
