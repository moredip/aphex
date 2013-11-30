#pragma once

class Task;

class Watchdog{
public:
  Watchdog( Task *alert, unsigned int timeout );

  void assuage();
  void slice();

private:
  Task *_alert;
  const unsigned int _timeout;
  long _lastAssuaged;

};
