#include "Arduino.h"
#include "light.h"
#include "color.h"

Light::Light(int redPin, int bluePin, int greenPin){
  _redPin = redPin;
  _bluePin = bluePin;
  _greenPin = greenPin;
}

void Light::setup(){
  pinMode( _redPin, OUTPUT );
  pinMode( _greenPin, OUTPUT );
  pinMode( _bluePin, OUTPUT );
}

void Light::displayColor( const Color &color ){
  displayRGB( color.redValue(), color.greenValue(), color.blueValue() );
}

void Light::displayRGB( int red, int blue, int green ){
  analogWrite( _redPin, constrain(red, 0, 255) );
  analogWrite( _bluePin, constrain(blue, 0, 255) );
  analogWrite( _greenPin, constrain(green, 0, 255) );
}
