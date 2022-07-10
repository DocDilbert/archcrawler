#pragma once
#include <memory>

#include "regscan/matchers/i_iter.h"
#include "regscan/matchers/i_matcher.h"
#include "regscan/matchers/i_search_file_buf.h"
#include "regscan/matchers/matchers_logger.h"
#include "regscan/memory_loader/file_buf.h"

class UcSearchFileBuf : private MatchersLogger, public ISearchFileBuf {
 public:
  UcSearchFileBuf();

  std::unique_ptr<IIter<Match>> Search(IMatcher& matcher, const file_buf_ptr& file_buf) override;

 private:
};
