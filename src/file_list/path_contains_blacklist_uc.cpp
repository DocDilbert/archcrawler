#include "regscan/file_list/path_contains_blacklist_uc.h"

PathContainsBlacklistUc::PathContainsBlacklistUc(str_vec black_list) : FileListLogger(), black_list_(black_list) {}

bool PathContainsBlacklistUc::is_rejected(const DirEntry& dir_entry) {
  auto path_string = dir_entry.path.string();
  for (auto& i : black_list_) {
    if (path_string.find(i) != std::string::npos) {
      logger_->trace("PathContainsBlacklistUc::is_rejected -> True for {}", path_string);
      return true;
    }
  }

  return false;
}

