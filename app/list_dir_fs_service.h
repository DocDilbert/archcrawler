#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <filesystem>
#include <sstream>
#include <string>
#include <vector>

#include "regscan/i_list_dir_service.h"

class ListDirFsService : public IListDirService {
 public:
  std::vector<DirEntry> ListDir(std::string path) {
    std::vector<DirEntry> dirs;
    spdlog::stopwatch sw;
    const std::filesystem::path sandbox{path};
    spdlog::trace("ListDirFsService::ListDir({})", path);

    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : std::filesystem::directory_iterator{sandbox}) {
      DirEntry de = {};
      de.fullpath = dir_entry.path().string();
      if (dir_entry.is_directory()) {
        de.is_dir = true;
      } else if (dir_entry.is_regular_file()) {
        de.is_file = true;
      }
      dirs.push_back(de);
    }
    spdlog::trace("ListDirFilesystem::ListDir elapsed={:.3}", sw);
    return dirs;
  }
};
