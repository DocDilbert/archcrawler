#pragma once
#include <stdlib.h>

#include "archcrawler/memory_loader/memory_loader_logger.h"

class FileBuf : private MemoryLoaderLogger {
 public:
  FileBuf(std::string fname, long fsize) : MemoryLoaderLogger(), fname_(fname), fsize_(fsize) {
    logger_->trace("FileBuf::FileBuf {} called with size {}", fname, fsize_);
    buf_ = reinterpret_cast<char*>(malloc(fsize_));
  }

  virtual ~FileBuf() {
    logger_->trace("FileBuf::~FileBuf {} called.");
    delete buf_;
  }

  std::string GetFilename() { return fname_; }

  char* GetBufferPtr() { return buf_; }

  long GetBufferSize() { return fsize_; }

 private:
  std::string fname_;
  long fsize_;
  char* buf_;
};
