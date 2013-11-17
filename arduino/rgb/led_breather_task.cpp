#include "led_breather_task.h"

#include "Arduino.h"

LedBreatherTask::LedBreatherTask( const int pin, const float period ) 
  : _pin(pin), _period(period)
{
  pinMode(_pin,OUTPUT);
}

void LedBreatherTask::slice() const {
  // courtesy of http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
  float val = (exp(sin(millis()/_period*PI)) - 0.36787944)*108.0;
  analogWrite(_pin, val);
}
