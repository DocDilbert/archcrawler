#pragma once

#include "regscan/dir_entry.h"

/// DirectoryWhiteList : IDirEntryPredicate
/// FileExtensionWhiteList : IDirEntryPredicate
class IDirEntryPredicate {
  public:
    /// Returns true when the given directory entry matches the predicate
    virtual bool is_accepted(DirEntry& dir_entry) = 0;

};
