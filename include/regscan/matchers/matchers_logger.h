#pragma once

#include <spdlog/spdlog.h>

#include "regscan/regscan_config.h"

class MatchersLogger {
 public:
  MatchersLogger() { logger_ = spdlog::get(regscan_matchers_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
