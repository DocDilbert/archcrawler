#pragma once

#include <string>

struct DirEntry {
  bool is_file;
  bool is_dir;
  std::string fullpath;
};
