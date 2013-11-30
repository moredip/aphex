#pragma once

#include "task.h"

class NullTask : public Task {
public:
  //virtual
  void slice() const {}
};
