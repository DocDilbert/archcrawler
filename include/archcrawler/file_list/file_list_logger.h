#pragma once

#include <spdlog/spdlog.h>

#include "archcrawler/archcrawler_config.h"

class FileListLogger {
 public:
  FileListLogger() { logger_ = spdlog::get(archcrawler_file_list_logger_name); }

 protected:
  std::shared_ptr<spdlog::logger> logger_;
};
