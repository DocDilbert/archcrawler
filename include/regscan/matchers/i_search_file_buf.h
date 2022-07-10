#pragma once

#include "regscan/memory_loader/file_buf.h"
#include "regscan/matchers/i_matcher.h"

class ISearchFileBuf {
  public:

  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  virtual std::unique_ptr<IMatchIter> Search(IMatcher& matcher, const file_buf_ptr& file_buf) = 0;
};
