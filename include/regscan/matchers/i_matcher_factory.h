#pragma once

#include <memory>
#include <string>

#include "regscan/matchers/i_matcher.h"

class IMatcherFactory {
 public:
  virtual ~IMatcherFactory() {}
  virtual std::unique_ptr<IMatcher> Create(std::string pattern) = 0;
};

