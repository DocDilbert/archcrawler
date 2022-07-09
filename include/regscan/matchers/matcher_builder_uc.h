#pragma once

#include <string>

#include "regscan/matchers/i_create_abstract_matcher_uc.h"
#include "regscan/matchers/i_register_matcher_uc.h"

class MatcherBuilderUc {
 public:
  MatcherBuilderUc(ICreateAbstractMatcherUc& create_abstract_matcher_uc, IRegisterMatcherUc& register_matcher_uc)
      : create_abstract_matcher_uc_(create_abstract_matcher_uc), register_matcher_uc_(register_matcher_uc) {}

  void Build(std::string matcher_factory_name, std::string matcher_name, std::string pattern) {
    auto matcher = create_abstract_matcher_uc_.Create(matcher_factory_name, pattern);
    register_matcher_uc_.Register(matcher_name, std::move(matcher));
  }

 private:
  ICreateAbstractMatcherUc& create_abstract_matcher_uc_;
  IRegisterMatcherUc& register_matcher_uc_;
};
