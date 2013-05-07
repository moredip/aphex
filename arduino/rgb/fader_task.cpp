#include "fader_task.h"

#include "Arduino.h"
#include "serial_stream.h"

FaderTask::FaderTask( const Light &light, const Color &leftColor, const Color &rightColor, const int duration )
  : _light(light), _leftColor(leftColor), _rightColor(rightColor), _duration(duration)
{}

void FaderTask::slice() const{
  long normalizedMillis = millis() % (_duration<<1);

  float distance = fabs( (float)(_duration - normalizedMillis)/_duration );

  _light.displayColor( _leftColor.tween( _rightColor, distance ) );
}
