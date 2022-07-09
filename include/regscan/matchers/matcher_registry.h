#pragma once
#include <map>
#include <memory>
#include <string>

#include "regscan/matchers/i_matcher.h"
#include "regscan/matchers/matchers_logger.h"

class MatcherRegistry : MatchersLogger {
 public:
  typedef std::unique_ptr<IMatcher> i_matcher_ptr;
  typedef std::map<std::string, i_matcher_ptr> i_matcher_set;
  typedef i_matcher_set::const_iterator iter;

  MatcherRegistry() : MatchersLogger() {}

  virtual ~MatcherRegistry() {}

  void Register(std::string matcher_id, i_matcher_ptr matcher) {
    logger_->debug("MatcherRegistry::Register Matcher \"{}\"", matcher_id);

    matchers_.emplace(matcher_id, std::move(matcher));
  }

 private:
  i_matcher_set matchers_;
};
