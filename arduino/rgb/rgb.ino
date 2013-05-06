#include "serial_stream.h"

int redLed = 9;
int greenLed = 10;
int blueLed = 11;

void setup() {                
  pinMode( redLed, OUTPUT );
  pinMode( greenLed, OUTPUT );
  pinMode( blueLed, OUTPUT );
  
  Serial.begin(57600);
}

int readAndParseColor(char *buffer, int offset){
  static char colorBuffer[3];
  memcpy( colorBuffer, buffer+offset, 2 );
  colorBuffer[2] = '\0';
  return strtol( colorBuffer, NULL, 16 );
}

void readRGB( int &red, int &green, int &blue ){
  
  char rawBytes[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
  Serial.readBytes( rawBytes, 6 );
  Serial << "received " << rawBytes << '\n';
  
  red = readAndParseColor(rawBytes,0);
  green = readAndParseColor(rawBytes,2);
  blue = readAndParseColor(rawBytes,4);
}

void displayRGB( int red, int green, int blue ){
  Serial << "rgb(" <<  red << "," << green << "," << blue << ")\n";
  analogWrite( redLed, constrain(red, 0, 255) );
  analogWrite( blueLed, constrain(blue, 0, 255) );
  analogWrite( greenLed, constrain(green, 0, 255) );
}

void loop() {
  if( !Serial.available() ) return;
 
  int redValue, greenValue, blueValue;  
  readRGB( redValue, greenValue, blueValue );
  displayRGB( redValue, greenValue, blueValue );
}

