#pragma once

#include "regscan/matchers/i_matcher.h"
#include "regscan/memory_loader/file_buf.h"

class ISearchFileBuf {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  virtual std::unique_ptr<IIter<MatchGroup>> Search(IMatcher& matcher, const file_buf_ptr& file_buf) = 0;
};
