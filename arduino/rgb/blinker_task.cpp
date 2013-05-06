#include "Arduino.h"
#include "blinker_task.h"

BlinkerTask::BlinkerTask( const Color &color, const Light &light, const int rate )
  : _color(color), _light(light), _rate(rate), _disabled(false)
{}

void BlinkerTask::slice() const{
  if( _disabled ) return;

  long normalizedMillis = millis() % (_rate<<1);
  if( normalizedMillis < _rate ){
    _light.off();
  }else{
    _light.displayColor( _color );
  }
}

void BlinkerTask::disable(){ _disabled = true; }
void BlinkerTask::enable(){ _disabled = false; }
