#pragma once

#include <memory>
#include <string>

#include "regscan/matchers/i_register_matcher_uc.h"
#include "regscan/matchers/matcher_registry.h"

class RegisterMatcherUc : public IRegisterMatcherUc {
 public:
  RegisterMatcherUc(MatcherRegistry& matcher_registry) : matcher_registry_(matcher_registry) {}

  void Register(std::string matcher_name, std::unique_ptr<IMatcher> matcher) override { matcher_registry_.Register(matcher_name, std::move(matcher)); }

 private:
  MatcherRegistry& matcher_registry_;
};
