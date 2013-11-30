#pragma once

#include "color.h"
#include "light.h"

#include "task.h"

class FaderTask : public Task {
public:
  FaderTask( const Light &light, const Color &leftColor, const Color &rightColor, const int duration );

  //virtual
  void slice() const;

private:
  const Light _light;
  const Color _leftColor;
  const Color _rightColor;
  const int _duration;
};
