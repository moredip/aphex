#include "Arduino.h"
#include "blinker_task.h"

BlinkerTask::BlinkerTask( const Light &light, const Color &color, const int rate )
  : Task(), _color(color), _light(light), _rate(rate)
{}

void BlinkerTask::slice() const{
  if( shouldSkipSlice() ) return;

  long normalizedMillis = millis() % (_rate<<1);
  if( normalizedMillis < _rate ){
    _light.off();
  }else{
    _light.displayColor( _color );
  }
}
