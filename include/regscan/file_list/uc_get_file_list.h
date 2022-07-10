#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string>
#include <vector>

#include "regscan/file_list/file_list_logger.h"
#include "regscan/file_list/i_dir_entry_predicate.h"
#include "regscan/file_list/i_list_dir_service.h"

class GetFileListUseCase : private FileListLogger {
 public:
  typedef std::vector<std::string> str_vector;
  typedef std::vector<std::shared_ptr<IDirEntryPredicate>> dir_entry_predicates_type;

  GetFileListUseCase(IListDirService& list_dir_service, dir_entry_predicates_type dir_entry_predicates);

  str_vector GetFileList(std::string path);

 private:
  str_vector GetFileListFromDir(std::string path);
  IListDirService& list_dir_service_;
  dir_entry_predicates_type dir_entry_predicates_;
};

