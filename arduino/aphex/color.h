#pragma once

class Stream;

class Color {
public:
  Color();
  Color( const char *webHexString );
  Color( int red, int green, int blue );

  // distance is between 0 and 1. 0 would return this color, 1 would return the otherColor.
  Color tween( const Color &other, float distance ) const;

  int redValue() const;
  int blueValue() const;
  int greenValue() const;
  void describe(Stream &s) const;

private:
  void init( int red, int green, int blue );
  int _red, _blue, _green;
};
