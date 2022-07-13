#pragma once

#include <map>
#include <memory>
#include <string>

#include "archcrawler/matchers/i_matcher.h"
#include "archcrawler/matchers/i_matcher_factory.h"
#include "archcrawler/matchers/matchers_logger.h"

class MatcherFactoryRegistry : MatchersLogger {
 public:
  MatcherFactoryRegistry() : MatchersLogger(), factories_() {}

  virtual ~MatcherFactoryRegistry() {}

  std::unique_ptr<IMatcher> Create(std::string matcher_factory_name, std::string pattern) {
    logger_->debug("MatcherFactoryRegistry::Create Matcher \"{}\":\"{}\"", matcher_factory_name, pattern);

    return factories_[matcher_factory_name]->Create(pattern);
  }

  void Register(std::string matcher_factory_name, std::unique_ptr<IMatcherFactory> matcher_factory) {
    logger_->debug("MatcherFactoryRegistry::Register factory \"{}\"", matcher_factory_name);
    factories_.emplace(matcher_factory_name, std::move(matcher_factory));
  }

 private:
  std::map<std::string, std::unique_ptr<IMatcherFactory>> factories_;
};
