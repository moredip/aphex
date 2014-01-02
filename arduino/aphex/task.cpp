#include "task.h"

Task::Task() : _disabled(false)
{}

bool Task::shouldSkipSlice() const{
  return _disabled;
}

void Task::disable(){ _disabled = true; }
void Task::enable(){ _disabled = false; }
