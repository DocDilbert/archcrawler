#include "regscan/file_list/path_beginswith_blacklist_uc.h"

PathBeginswithBlacklistUc::PathBeginswithBlacklistUc(str_vec black_list) : FileListLogger(), black_list_(black_list) {}

bool PathBeginswithBlacklistUc::is_rejected(const DirEntry& dir_entry) {
  auto path_string = dir_entry.path.string();
  for (auto& i : black_list_) {
    if (path_string.rfind(i, 0) == 0) {
      logger_->trace("PathBeginswithBlacklistUc::is_rejected -> True for {}", path_string);
      return true;
    }
  }

  return false;
}

