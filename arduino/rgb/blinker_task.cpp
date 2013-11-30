#include "Arduino.h"
#include "blinker_task.h"

BlinkerTask::BlinkerTask( const Light &light, const Color &firstColor, const Color &secondColor, const int rate )
  : Task(), _firstColor(firstColor), _secondColor(secondColor), _light(light), _rate(rate)
{}

void BlinkerTask::slice() const{
  if( shouldSkipSlice() ) return;

  long normalizedMillis = millis() % (_rate<<1);
  if( normalizedMillis < _rate ){
    _light.displayColor( _firstColor );
  }else{
    _light.displayColor( _secondColor );
  }
}
