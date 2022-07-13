#pragma once

#include "archcrawler/matchers/i_matcher.h"
#include "archcrawler/memory_loader/file_buf.h"
#include "archcrawler/matchers/i_iter.h"
#include "archcrawler/matchers/match_in_file.h"

class ISearchInFileBufList {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  typedef std::vector<file_buf_ptr> file_buf_list;

  virtual std::unique_ptr<IIter<MatchInFile>> Search(IMatcher& matcher, const file_buf_list& fblist) = 0;
};
