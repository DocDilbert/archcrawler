#pragma once

#include <memory>
#include <string>

#include "archcrawler/matchers/i_matcher_factory.h"

class IRegisterMatcherFactory {
 public:
  virtual void Register(std::string matcher_factory_name, std::unique_ptr<IMatcherFactory> matcher_factory) = 0;
};

