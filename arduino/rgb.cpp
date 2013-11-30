#include "Arduino.h"

#include "rgb/serial_stream.h"
#include "rgb/null_task.h"
#include "rgb/led_strober_task.h"
#include "rgb/fader_task.h"
#include "rgb/blinker_task.h"
#include "rgb/watchdog.h"

#define ONBOARD_LED (13)
//#define WATCHDOG_TIMEOUT (120000) //2 minutes
#define WATCHDOG_TIMEOUT (20000)


//Light light(9,10,11);
Light light(3,5,6);
Color purple("ff00ff");
Color off("000000");

FaderTask watchdogAlert = FaderTask(light, Color("000033"), Color("333300"),2000);
Watchdog watchdog = Watchdog( &watchdogAlert, WATCHDOG_TIMEOUT );

FaderTask fader = FaderTask(light,Color("ff0000"),Color("00ff10"),1000);
LedStroberTask led13Task = LedStroberTask(ONBOARD_LED,1000.0);

//void establishContact() {
  //while (!Serial) {
    //// wait   for serial port to connect. Needed for Leonardo only
    //digitalWrite(13,HIGH); delay(100); digitalWrite(13,LOW); delay(1000);
  //}

  //while (Serial.available() <= 0) {
    //Serial.println("waiting...");
    //digitalWrite(13,HIGH); delay(200); digitalWrite(13,LOW); delay(50);
  //}
//}


void setup() {                
  light.setup();
  
  Serial.begin(57600);

  watchdog.forceFail();

  //establishContact();
}

const Color readRGB(bool &readSucceeded){
  char rawBytes[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
  int bytesRead = Serial.readBytes( rawBytes, 6 );
  readSucceeded = bytesRead == 6;
  return Color( rawBytes );
}

const int readDuration(){
  return Serial.parseInt();
}

const bool readSpace(){
  char buffer[] = {NULL};
  Serial.readBytes( buffer, 1 );
  return buffer[0] == ' ';
}

Task *readInput(){
  bool readSucceeded = false;
  const Color startingColor = readRGB(readSucceeded);
  if( !readSucceeded )
  {
    Serial << "invalid input (input sequence was too slow)\n";
    return NULL;
  }

  if( !readSpace() )
  {
    Serial << "invalid input (expected a space seperator between first and second RGB fields)\n";
    return NULL;
  }
  
  const Color endingColor = readRGB(readSucceeded);
  if( !readSucceeded )
  {
    Serial << "invalid input (input sequence was too slow)\n";
    return NULL;
  }

  if( !readSpace() )
  {
    Serial << "invalid input (expected a space seperator after second RGB field)\n";
    return NULL;
  }

  const int duration = readDuration();

  if( Serial.read() != '\n' )
  {
    Serial << "invalid input (expected a new-line terminator after the duration field)\n";
    return NULL;
  }
  
  Serial << "("; startingColor.describe( Serial ); Serial << ") -> ("; endingColor.describe( Serial );
  Serial << ") for "<<duration<<"\n";

  return new FaderTask(light,startingColor,endingColor,duration);
}

Task *inputtedTask = new NullTask();

void loop() {
  led13Task.slice();
  watchdog.slice();

  if( !watchdog.isFailed() ){
    inputtedTask->slice();
  }

  if( !Serial.available() ) return;

  watchdog.assuage();

  Task *nextInputtedTask = readInput();
  if( nextInputtedTask )
  {
    delete inputtedTask;
    inputtedTask = nextInputtedTask;
  }

  Serial << "ready!\n";
 
  //const Color color = readRGB();
  //color.describe( Serial ); Serial << '\n';
  //light.displayColor( color );
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
