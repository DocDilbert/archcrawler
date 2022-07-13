#pragma once

#include <spdlog/spdlog.h>

#include "archcrawler/archcrawler_config.h"

class MemoryLoaderLogger {
 public:
  MemoryLoaderLogger() { logger_ = spdlog::get(archcrawler_memory_loader_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
