#pragma once

class BlinkerTask;

class Watchdog{
public:
  Watchdog( BlinkerTask *alert, unsigned int timeout );

  void assuage();
  void slice();

private:
  BlinkerTask *_alert;
  const unsigned int _timeout;
  long _lastAssuaged;

};
