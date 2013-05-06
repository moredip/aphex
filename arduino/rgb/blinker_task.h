#include "color.h"
#include "light.h"

class BlinkerTask {
public:
  BlinkerTask( const Color &color, const Light &light, const int rate );

  void slice() const;

  void disable();

private:
  const Color _color;
  const Light _light;
  const int _rate;
  bool _disabled;
};
