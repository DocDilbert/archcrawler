#pragma once
#include <memory>

#include "archcrawler/memory_loader/file_buf.h"
#include "archcrawler/memory_loader/i_load_file_service.h"
#include "archcrawler/memory_loader/memory_loader_logger.h"

class UcLoadFileList : private MemoryLoaderLogger {
 public:
  typedef std::vector<std::string> str_vector;
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  typedef std::vector<file_buf_ptr> file_buf_list;

  UcLoadFileList(ILoadFileService& load_file_service);

  file_buf_list Load(str_vector fname_list);

 private:
  ILoadFileService& load_file_service_;
};
