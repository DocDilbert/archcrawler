#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>

struct RegexCompileException : public std::exception {
  RegexCompileException(int error_offset, std::string error_message) : error_offset(error_offset), error_message(error_message) {}

  int error_offset;
  std::string error_message;
};

struct RegexSearchException : public std::exception {
  RegexSearchException(int error_code) : error_code(error_code) {}
  int error_code;
};

struct RegexMatch {
  int begin_pos;
  int end_pos;
  int length;
};

class IRegexMatchIter {
 public:
  virtual ~IRegexMatchIter() {}
  virtual void Next() = 0;
  virtual RegexMatch Current() = 0;
  virtual bool IsDone() = 0;
};

class IMatcher {
 public:
  virtual ~IMatcher(){};
  virtual std::unique_ptr<IRegexMatchIter> Search(const char* subject) = 0;
};

class IMatcherFactory {
 public:
  virtual ~IMatcherFactory() {}
  virtual std::unique_ptr<IMatcher> Create(std::string pattern) = 0;
};

class Regex : public IMatcher {
 public:
  Regex(std::string pattern);
  virtual ~Regex();

  virtual std::unique_ptr<IRegexMatchIter> Search(const char* subject);

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
