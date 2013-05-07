#include "serial_stream.h"
#include "color.h"

int readAndParseColor(const char *buffer, int offset){
  static char colorBuffer[3];
  memcpy( colorBuffer, buffer+offset, 2 );
  colorBuffer[2] = '\0';
  return strtol( colorBuffer, NULL, 16 );
}

void Color::init( int red, int green, int blue )
{
  _red = red;
  _green = green;
  _blue = blue;
}

Color::Color( const char *webHexString ){
  init( 
      readAndParseColor(webHexString,0),
      readAndParseColor(webHexString,2),
      readAndParseColor(webHexString,4)
  );
}

Color::Color( int red, int green, int blue )
{
  init( red, green, blue );
}

int tween( int thisVal, int otherVal, float distance ){
  int range = otherVal-thisVal;
  return thisVal + (distance*range);
}

Color Color::tween( const Color &other, float distance ) const {
  return Color( 
      ::tween( _red, other._red, distance ),
      ::tween( _blue, other._blue, distance ),
      ::tween( _green, other._green, distance )
  );
}

void Color::describe(Stream &s) const{
  s << "rgb(" <<  _red << "," << _green << "," << _blue << ")";
}

int Color::redValue() const{ return _red; }
int Color::blueValue() const{ return _blue; }
int Color::greenValue() const{ return _green; }
