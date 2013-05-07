#pragma once

#include "color.h"
#include "light.h"

class FaderTask {
public:
  FaderTask( const Light &light, const Color &leftColor, const Color &rightColor, const int duration );

  void slice() const;

private:
  const Light _light;
  const Color _leftColor;
  const Color _rightColor;
  const int _duration;
};
