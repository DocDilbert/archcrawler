#pragma once

#include <spdlog/spdlog.h>

#include "regscan/regscan_config.h"

class MemoryLoaderLogger {
 public:
  MemoryLoaderLogger() { logger_ = spdlog::get(regscan_memory_loader_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
