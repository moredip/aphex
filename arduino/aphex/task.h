#pragma once

class Task{
public:
  Task();
  virtual void slice() const = 0;

  void disable();
  void enable();

protected:
  bool shouldSkipSlice() const;

private:
  bool _disabled;
};
