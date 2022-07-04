#pragma once

#include <string>
#include <vector>

struct DirEntry {
  bool is_file;
  bool is_dir;
  std::string fullpath;
};

class IListDirService {
 public:
  virtual std::vector<DirEntry> ListDir(std::string path) = 0;
};
