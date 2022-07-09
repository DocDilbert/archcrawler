#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

#include "regscan/matchers/i_match_iter.h"
#include "regscan/matchers/i_matcher.h"
#include "regscan/matchers/i_matcher_factory.h"

struct RegexCompileException : public std::exception {
  RegexCompileException(int error_offset, std::string error_message) : error_offset(error_offset), error_message(error_message) {}

  int error_offset;
  std::string error_message;
};

struct RegexSearchException : public std::exception {
  RegexSearchException(int error_code) : error_code(error_code) {}
  int error_code;
};

class Regex : public IMatcher {
 public:
  Regex(std::string pattern);
  virtual ~Regex();

  virtual std::unique_ptr<IMatchIter> Search(const char* subject);

 private:
  struct impl;
  std::unique_ptr<impl> pimpl_;  // opaque type here
  std::shared_ptr<spdlog::logger> logger_;
};

class RegexFactory : public IMatcherFactory {
 public:
  virtual ~RegexFactory() {}
  virtual std::unique_ptr<IMatcher> Create(std::string pattern) { return std::make_unique<Regex>(pattern); }
};
