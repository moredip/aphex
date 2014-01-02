#include "input.h"

#include "Arduino.h"

#include "serial_stream.h"
#include "fader_task.h"

class Input {
  public:
    Input( const Light &light );

    void readTask();

    Task *parsedTask() const;
    void describeParsedInput();

  private:

    bool readColor( Color &color);
    bool readFirstColor();
    bool readSecondColor();
    bool readDuration();

    void reportParsingError( const char *details );

    const Light _light;
    Color _firstColor;
    Color _secondColor;
    int _duration;

    const char *_parsingStage;

    Task *_parsedTask;
};

Task *input_parse_task( const Light &light )
{
  Input input = Input(light);
  input.readTask();
  input.describeParsedInput();

  return input.parsedTask();
}

Input::Input( const Light &light ) : _light(light), _duration(0), _parsingStage(""), _parsedTask(NULL) {}

const Color readRGB(bool &readSucceeded){
  char rawBytes[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL};
  Serial.readBytes( rawBytes, 6 );

  // will also fail if read times out
  readSucceeded = isxdigit(rawBytes[0]) 
    && isxdigit(rawBytes[1])
    && isxdigit(rawBytes[2])
    && isxdigit(rawBytes[3])
    && isxdigit(rawBytes[4])
    && isxdigit(rawBytes[5]);

  return Color( rawBytes );
}


const bool readSpace(){
  char buffer[] = {NULL};
  Serial.readBytes( buffer, 1 );
  return buffer[0] == ' ';
}

const bool readNewLine(){
  char buffer[] = {NULL};
  Serial.readBytes( buffer, 1 );
  return buffer[0] == '\n' || buffer[0] == '\r';
}

void Input::readTask(){
  if( !readFirstColor() )
    return;

  if( !readSecondColor() )
    return;
  
  if( !readDuration() )
    return;

  _parsedTask = new FaderTask(_light,_firstColor,_secondColor,_duration);
}

bool Input::readColor( Color &color){
  bool readSucceeded = false;
  color = readRGB(readSucceeded);
  if( !readSucceeded )
  {
    reportParsingError( "invalid or incomplete RGB hex value (expected a 6-digit value without a leading #)" );
    return false;
  }

  if( !readSpace() )
  {
    reportParsingError( "expected a trailing space seperator" );
    return false;
  }

  return true;
}

bool Input::readFirstColor(){
  _parsingStage = "reading first color";
  return readColor( _firstColor );
}

bool Input::readSecondColor(){
  _parsingStage = "reading second color";
  return readColor( _secondColor );
}

void Input::describeParsedInput(){ 
  Serial << "("; _firstColor.describe( Serial ); Serial << ") -> ("; _secondColor.describe( Serial );
  Serial << ") over "<<_duration<<"ms\n";
}

void Input::reportParsingError( const char *details ){
    Serial << "parsing error while "<<_parsingStage<<": "<<details<<"\n";
}

bool Input::readDuration(){
  _parsingStage = "reading duration";
  _duration = Serial.parseInt();

  if( !readNewLine() )
  {
    reportParsingError( "expected a terminating new line afterwards" );
    return false;
  }
  return true;
}

Task *Input::parsedTask() const{
  return _parsedTask;
}
