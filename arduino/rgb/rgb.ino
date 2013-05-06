#include "serial_stream.h"
#include "blinker_task.h"
#include "watchdog.h"

Light light(9,10,11);
Color purple("ffff00");
BlinkerTask awaitingOrders = BlinkerTask(purple,light,800);
Watchdog watchdog = Watchdog( &awaitingOrders, 10000 );

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
  awaitingOrders.slice();
  watchdog.slice();

  if( !Serial.available() ) return;

  awaitingOrders.disable();
  watchdog.assuage();
 
  const Color color = readRGB();
  color.describe( Serial ); Serial << '\n';
  light.displayColor( color );
}

