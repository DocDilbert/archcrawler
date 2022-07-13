#pragma once

#include <spdlog/spdlog.h>

#include <string>
#include <vector>

#include "archcrawler/file_list/file_list_logger.h"
#include "archcrawler/file_list/i_dir_entry_predicate.h"

class UcFileExtensionWhitelist : public IDirEntryPredicate, private FileListLogger {
 public:
  typedef std::vector<std::string> str_vec;

  UcFileExtensionWhitelist(str_vec white_list);

  bool is_rejected(const DirEntry& dir_entry) override;

 private:
  str_vec white_list_;
};
