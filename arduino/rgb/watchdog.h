#pragma once

class Task;

class Watchdog{
public:
  Watchdog( Task *alert, unsigned long timeout );

  bool isFailed() const;

  void forceFail();
  void assuage();
  void slice();

private:
  Task *_alert;
  const unsigned long _timeout;
  long _lastAssuaged;

};
