#pragma once

#include <spdlog/spdlog.h>

#include <string>
#include <vector>

#include "regscan/file_list/file_list_logger.h"
#include "regscan/file_list/i_dir_entry_predicate.h"

class UcPathBeginswithBlacklist : public IDirEntryPredicate, private FileListLogger {
 public:
  typedef std::vector<std::string> str_vec;

  UcPathBeginswithBlacklist(str_vec black_list);

  bool is_rejected(const DirEntry& dir_entry) override;

 private:
  str_vec black_list_;
};
