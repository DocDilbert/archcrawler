
#pragma once

#include <memory>
#include <string>

#include "regscan/matchers/i_register_matcher_factory.h"
#include "regscan/matchers/matcher_factory_registry.h"

class UcRegisterMatcherFactory : public IRegisterMatcherFactory {
 public:
  UcRegisterMatcherFactory(MatcherFactoryRegistry& matcher_factory_registry) : matcher_factory_registry_(matcher_factory_registry) {}

  void Register(std::string matcher_factory_name, std::unique_ptr<IMatcherFactory> matcher_factory) override {
    matcher_factory_registry_.Register(matcher_factory_name, std::move(matcher_factory));
  }

 private:
  MatcherFactoryRegistry& matcher_factory_registry_;
};
