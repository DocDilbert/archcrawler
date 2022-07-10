#pragma once

#include "regscan/matchers/i_matcher.h"
#include "regscan/memory_loader/file_buf.h"

class ISearchInFileBufList {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  typedef std::vector<file_buf_ptr> file_buf_list;

  virtual void Search(IMatcher& matcher, const file_buf_list& fblist) = 0;
};
