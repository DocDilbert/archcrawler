#pragma once
#include <memory>

#include "regscan/matchers/i_match_iter.h"

class IMatcher {
 public:
  virtual ~IMatcher(){};
  virtual std::unique_ptr<IIter<Match>> Search(const char* subject) = 0;
};
