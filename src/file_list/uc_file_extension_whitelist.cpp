#include "archcrawler/file_list/uc_file_extension_whitelist.h"

UcFileExtensionWhitelist::UcFileExtensionWhitelist(str_vec white_list) : FileListLogger(), white_list_(white_list) {}

bool UcFileExtensionWhitelist::is_rejected(const DirEntry& dir_entry) {
  bool reject = false;
  if (dir_entry.is_file) {
    reject = true;  // forbid every file with extensions not on the whitelist
    auto extension_string = dir_entry.path.extension().string();
    for (auto& i : white_list_) {
      if (extension_string.find(i) != std::string::npos) {
        reject = false;
        break;
      }
    }

    if (reject) {
      logger_->trace("UcFileExtensionWhitelist::is_rejected -> True for {}", dir_entry.path.string());
    }
  }
  return reject;
}

