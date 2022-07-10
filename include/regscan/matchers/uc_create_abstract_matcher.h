#pragma once

#include <string>

#include "regscan/matchers/i_create_abstract_matcher_uc.h"
#include "regscan/matchers/matcher_factory_registry.h"

class CreateAbstractMatcherUc : public ICreateAbstractMatcherUc {
 public:
  CreateAbstractMatcherUc(MatcherFactoryRegistry& matcher_factory_registry) : matcher_factory_registry_(matcher_factory_registry) {}

  std::unique_ptr<IMatcher> Create(std::string matcher_factory_name, std::string pattern) override {
    auto matcher = matcher_factory_registry_.Create(matcher_factory_name, pattern);
    return matcher;
  }

 private:
  MatcherFactoryRegistry& matcher_factory_registry_;
};
