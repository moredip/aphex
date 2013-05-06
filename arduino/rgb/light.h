class Color;

class Light {
public:
  Light(int redPin, int bluePin, int greenPin );

  void setup();

  void displayColor( const Color &color );
  void displayRGB( int red, int blue, int green );
    
private:
  int _redPin, _bluePin, _greenPin;
};
