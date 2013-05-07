#pragma once

#include "color.h"
#include "light.h"

class BlinkerTask {
public:
  BlinkerTask( const Light &light, const Color &color, const int rate );

  void slice() const;

  void disable();
  void enable();

private:
  const Color _color;
  const Light _light;
  const int _rate;
  bool _disabled;
};
