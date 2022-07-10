#pragma once

#include <memory>
#include <string>

#include "regscan/matchers/i_matcher_factory.h"

class IRegisterMatcherFactoryUc {
 public:
  virtual void Register(std::string matcher_factory_name, std::unique_ptr<IMatcherFactory> matcher_factory) = 0;
};

