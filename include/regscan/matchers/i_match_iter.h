#pragma once

#include "regscan/matchers/match.h"

class IMatchIter {
 public:
  virtual ~IMatchIter() {}
  virtual void Next() = 0;
  virtual Match Current() = 0;
  virtual bool IsDone() = 0;
};
