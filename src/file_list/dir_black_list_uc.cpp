#include "regscan/file_list/dir_black_list_uc.h"

DirBlackListUc::DirBlackListUc(str_vec black_list) : FileListLogger(), black_list_(black_list) {}

bool DirBlackListUc::is_rejected(const DirEntry& dir_entry) {
  if (dir_entry.is_dir) {
    auto path_string = dir_entry.path.string();
    for (auto& i : black_list_) {
      if (path_string.compare(i) == 0) {
        logger_->debug("DirBlackListUc::is_rejected -> True for {}", path_string);
        return true;
      }
    }

    logger_->trace("DirBlackListUc::is_rejected -> False for {}", path_string);
    return false;
  }
  return false;
}

