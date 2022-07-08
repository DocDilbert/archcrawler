#pragma once

#include "regscan/memory_loader/file_buf.h"

class ILoadFileService {
 public:
  virtual std::shared_ptr<FileBuf> LoadFile(std::string fname) = 0;
};
