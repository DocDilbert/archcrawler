#pragma once

#include <memory>

#include "regscan/matchers/i_matcher.h"

class ICreateAbstractMatcherUc {
 public:
  virtual std::unique_ptr<IMatcher> Create(std::string matcher_factory_name, std::string pattern) = 0;
};
