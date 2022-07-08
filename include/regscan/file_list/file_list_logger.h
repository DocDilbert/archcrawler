#pragma once

#include <spdlog/spdlog.h>

#include "regscan/regscan_config.h"

class FileListLogger {
 public:
  FileListLogger() { logger_ = spdlog::get(regscan_file_list_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
