#pragma once

#include <filesystem>
#include <string>

struct DirEntry {
  bool is_file;
  bool is_dir;
  std::filesystem::path path; 
};
