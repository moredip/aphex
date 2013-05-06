#include "serial_stream.h"
#include "light.h"
#include "color.h"

Light light(9,10,11);

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
  if( !Serial.available() ) return;
 
  const Color color = readRGB();
  color.describe( Serial ); Serial << '\n';
  light.displayColor( color );
}

