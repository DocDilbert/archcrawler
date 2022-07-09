#pragma once
#include <memory>

#include "regscan/memory_loader/file_buf.h"
#include "regscan/memory_loader/i_load_file_service.h"
#include "regscan/memory_loader/memory_loader_logger.h"

class LoadFileListUc : private MemoryLoaderLogger {
 public:
  typedef std::vector<std::string> str_vector;
  typedef std::unique_ptr<FileBuf> file_ptr;
  typedef std::vector<file_ptr> file_list;

  LoadFileListUc(ILoadFileService& load_file_service);

  file_list Load(str_vector fname_list);

 private:
  ILoadFileService& load_file_service_;
};
