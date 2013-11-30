#include "fader_task.h"

#include "Arduino.h"
#include "serial_stream.h"

#define SQR(X) ((X)*(X))

FaderTask::FaderTask( const Light &light, const Color &leftColor, const Color &rightColor, const int duration )
  : Task(), _light(light), _leftColor(leftColor), _rightColor(rightColor), _duration(duration)
{}

void FaderTask::slice() const{
  if( shouldSkipSlice() ) return;

  long normalizedMillis = millis() % (_duration<<1);

  float distance = fabs( (float)(_duration - normalizedMillis)/_duration );
  float easedDistance = SQR(distance) / ( SQR(distance) + SQR(1-distance) );

  _light.displayColor( _leftColor.tween( _rightColor, easedDistance ) );
}
