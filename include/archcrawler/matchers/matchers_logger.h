#pragma once

#include <spdlog/spdlog.h>

#include "archcrawler/archcrawler_config.h"

class MatchersLogger {
 public:
  MatchersLogger() { logger_ = spdlog::get(archcrawler_matchers_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
