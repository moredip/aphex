#include "Arduino.h"
#include "watchdog.h"
#include "task.h"

Watchdog::Watchdog( Task *alert, unsigned long timeout ) 
  : _alert(alert), _timeout(timeout)
{
  assuage();
}

bool Watchdog::isFailed() const {
  return ( millis() - _lastAssuaged > _timeout );
}


void Watchdog::assuage(){
  _lastAssuaged = millis();
  _alert->disable();
}

void Watchdog::forceFail(){
  _lastAssuaged = 0;
  _alert->enable();
}

void Watchdog::slice(){
  _alert->slice();

  if( isFailed() )
    _alert->enable();
}

