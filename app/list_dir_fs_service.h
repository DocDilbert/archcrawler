#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "app_config.h"
#include "regscan/file_list/i_list_dir_service.h"

class ListDirFsService : public IListDirService {
 public:
  ListDirFsService() { logger_ = spdlog::get(app_logger_name); }

  std::vector<DirEntry> ListDir(std::string path) {
    std::vector<DirEntry> dirs;
    spdlog::stopwatch sw;
    const std::filesystem::path sandbox{path};

    logger_->trace("ListDirFsService::ListDir({})", path);

    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) {
      DirEntry de = {};
      de.path = dir_entry.path();
      if (dir_entry.is_directory()) {
        de.is_dir = true;
      } else if (dir_entry.is_regular_file()) {
        de.is_file = true;
      }
      dirs.push_back(de);
    }
    logger_->trace("ListDirFilesystem::ListDir elapsed={:.3}", sw);
    return dirs;
  }

 private:
  std::shared_ptr<spdlog::logger> logger_;
};
