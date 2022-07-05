#pragma once

#include <string>
#include <vector>
#include "regscan/dir_entry.h"


class IListDirService {
 public:
  virtual std::vector<DirEntry> ListDir(std::string path) = 0;
};
