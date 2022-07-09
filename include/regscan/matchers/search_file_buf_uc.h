#pragma once
#include <memory>

#include "regscan/matchers/i_match_iter.h"
#include "regscan/matchers/i_matcher.h"
#include "regscan/matchers/matchers_logger.h"
#include "regscan/memory_loader/file_buf.h"

class SearchFileBufUc : private MatchersLogger {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;

  SearchFileBufUc(std::unique_ptr<IMatcher> matcher);

  std::unique_ptr<IMatchIter> Search(const file_buf_ptr& file_buf);

 private:
  std::unique_ptr<IMatcher> matcher_;
};
