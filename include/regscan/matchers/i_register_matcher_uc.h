#pragma once

#include <memory>
#include <string>

#include "regscan/matchers/i_matcher.h"

class IRegisterMatcherUc {
 public:
  virtual void Register(std::string matcher_name, std::unique_ptr<IMatcher> matcher) = 0;
};
