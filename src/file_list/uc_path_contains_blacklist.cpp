#include "archcrawler/file_list/uc_path_contains_blacklist.h"

UcPathContainsBlacklist::UcPathContainsBlacklist(str_vec black_list) : FileListLogger(), black_list_(black_list) {}

bool UcPathContainsBlacklist::is_rejected(const DirEntry& dir_entry) {
  auto path_string = dir_entry.path.string();
  for (auto& i : black_list_) {
    if (path_string.find(i) != std::string::npos) {
      logger_->trace("UcPathContainsBlacklist::is_rejected -> True for {}", path_string);
      return true;
    }
  }

  return false;
}

