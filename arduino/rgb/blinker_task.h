#pragma once

#include "color.h"
#include "light.h"

#include "task.h"

class BlinkerTask : public Task {
public:
  BlinkerTask( const Light &light, const Color &firstColor, const Color &secondColor, const int rate );

  //virtual
  void slice() const;

private:
  const Color _firstColor;
  const Color _secondColor;
  const Light _light;
  const int _rate;
};
