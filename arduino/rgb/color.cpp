#include "Arduino.h"
#include "serial_stream.h"
#include "color.h"

int readAndParseColor(const char *buffer, int offset){
  static char colorBuffer[3];
  memcpy( colorBuffer, buffer+offset, 2 );
  colorBuffer[2] = '\0';
  return strtol( colorBuffer, NULL, 16 );
}

Color::Color( const char *webHexString ){
  _red = readAndParseColor(webHexString,0);
  _green = readAndParseColor(webHexString,2);
  _blue = readAndParseColor(webHexString,4);
}

void Color::describe(Stream &s) const{
  s << "rgb(" <<  _red << "," << _green << "," << _blue << ")";
}

int Color::redValue() const{ return _red; }
int Color::blueValue() const{ return _blue; }
int Color::greenValue() const{ return _green; }
