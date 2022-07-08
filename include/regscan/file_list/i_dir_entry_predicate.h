#pragma once

#include "regscan/file_list/dir_entry.h"

class IDirEntryPredicate {
 public:
  /// Returns true when the given directory entry was rejected by the predicate
  virtual bool is_rejected(const DirEntry& dir_entry) = 0;
};
