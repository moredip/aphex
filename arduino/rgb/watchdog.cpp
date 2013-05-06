#include "Arduino.h"
#include "watchdog.h"
#include "blinker_task.h"

Watchdog::Watchdog( BlinkerTask *alert, unsigned int timeout ) 
  : _alert(alert), _timeout(timeout)
{
  assuage();
}

void Watchdog::assuage(){
  _lastAssuaged = millis();
}

void Watchdog::slice(){
  if( millis() - _lastAssuaged > _timeout )
    _alert->enable();
}

