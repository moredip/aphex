#include "Arduino.h"
#include "watchdog.h"
#include "task.h"

Watchdog::Watchdog( Task *alert, unsigned int timeout ) 
  : _alert(alert), _timeout(timeout)
{
  assuage();
}

void Watchdog::assuage(){
  _lastAssuaged = millis();
  _alert->disable();
}

void Watchdog::slice(){
  if( millis() - _lastAssuaged > _timeout )
    _alert->enable();
}

