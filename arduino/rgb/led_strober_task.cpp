#include "led_strober_task.h"

#include "Arduino.h"

LedStroberTask::LedStroberTask( const int pin, const int period ) 
  : _pin(pin), _period(period)
{
  pinMode(_pin,OUTPUT);
}

void LedStroberTask::slice() const {
  long normalizedMillis = millis() % _period;
  if( normalizedMillis < (_period>>1) ){
    digitalWrite( _pin, LOW );
  }else{
    digitalWrite( _pin, HIGH );
  }
}
