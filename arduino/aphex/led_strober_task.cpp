#include "led_strober_task.h"

#include "Arduino.h"

LedStroberTask::LedStroberTask( const int pin, const int onPeriod, const int offPeriod ) 
  : _pin(pin), _onPeriod(onPeriod), _offPeriod(offPeriod)
{
  pinMode(_pin,OUTPUT);
}

void LedStroberTask::slice() const {
  long normalizedMillis = millis() % (_onPeriod+_offPeriod);
  if( normalizedMillis < _onPeriod ){
    digitalWrite( _pin, HIGH );
  }else{
    digitalWrite( _pin, LOW );
  }
}
