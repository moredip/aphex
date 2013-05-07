#pragma once

class Color;

class Light {
public:
  Light(int redPin, int bluePin, int greenPin );

  void setup() const;

  void off() const;
  void displayColor( const Color &color ) const;
  void displayRGB( int red, int blue, int green ) const;
    
private:
  int _redPin, _bluePin, _greenPin;
};
