#include "regscan/file_list/uc_get_file_list.h"

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <iostream>

#include "regscan/regscan_config.h"

UcGetFileList::UcGetFileList(IListDirService& list_dir_service, UcGetFileList::dir_entry_predicates_type dir_entry_predicates)
    : FileListLogger(), list_dir_service_(list_dir_service), dir_entry_predicates_(dir_entry_predicates) {
  logger_ = spdlog::get(regscan_file_list_logger_name);
}

UcGetFileList::str_vector UcGetFileList::GetFileList(std::string path) {
  spdlog::stopwatch sw;
  logger_->info("UcGetFileList::GetFileList(\"{}\")", path);
  auto ret = GetFileListFromDir(path);
  logger_->debug("UcGetFileList::GetFileList elapsed={:.3}", sw);
  return ret;
}

UcGetFileList::str_vector UcGetFileList::GetFileListFromDir(std::string path) {
  str_vector ret;
  auto dirlist = list_dir_service_.ListDir(path);
  for (auto const& dir_entry : dirlist) {
    auto path_string = dir_entry.path.string();

    bool is_rejected = false;
    for (auto& dir_entry_predicate : dir_entry_predicates_) {
      if (dir_entry_predicate->is_rejected(dir_entry)) {
        is_rejected = true;
        logger_->trace("Predicate rejects DirEntry {}", path_string);
      }
    }

    if (is_rejected) {
      continue;
    }
    if (dir_entry.is_dir) {
      auto res_dir = GetFileListFromDir(path_string);
      ret.insert(ret.end(), res_dir.begin(), res_dir.end());
    } else if (dir_entry.is_file) {
      ret.push_back(path_string);
    }
  }
  return ret;
}
