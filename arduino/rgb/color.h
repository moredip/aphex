class Stream;

class Color {
public:
  Color( const char *webHexString );

  int redValue() const;
  int blueValue() const;
  int greenValue() const;
  void describe(Stream &s) const;

private:
  int _red, _blue, _green;
};
