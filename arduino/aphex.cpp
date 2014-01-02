#include "Arduino.h"

#include "rgb/serial_stream.h"
#include "rgb/null_task.h"
#include "rgb/led_strober_task.h"
#include "rgb/fader_task.h"
#include "rgb/blinker_task.h"
#include "rgb/watchdog.h"

#include "rgb/input.h"

#define ONBOARD_LED (13)
#define SERIAL_TIMEOUT (5000) // in millis
#define WATCHDOG_TIMEOUT (120000) //2 minutes


//Light light(9,10,11);
Light light(3,5,6);

FaderTask watchdogAlert = FaderTask(light, Color("000033"), Color("333300"),2000);
Watchdog watchdog = Watchdog( &watchdogAlert, WATCHDOG_TIMEOUT );

LedStroberTask led13Task = LedStroberTask(ONBOARD_LED,2000.0,100.0);

void setup() {                
  light.setup();
  
  Serial.begin(57600);
  Serial.setTimeout(SERIAL_TIMEOUT);

  watchdog.forceFail();
}

Task *inputtedTask = new NullTask();

void loop() {
  led13Task.slice();
  watchdog.slice();

  if( !watchdog.isFailed() ){
    inputtedTask->slice();
  }

  if( !Serial.available() ) return;

  Task *nextInputtedTask = input_parse_task(light);
  if( nextInputtedTask )
  {
    delete inputtedTask;
    inputtedTask = nextInputtedTask;
    watchdog.assuage();
  }
}


// standard Arduino main.cpp, copied from https://github.com/arduino/Arduino/blob/master/hardware/arduino/cores/arduino/main.cpp
int main(void)
{
  init();

  setup();
    
  for (;;) {
    loop();
    if (serialEventRun) serialEventRun();
  }
        
  return 0;
}
