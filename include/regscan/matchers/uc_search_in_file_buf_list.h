#pragma once
#include <memory>

#include "regscan/matchers/i_matcher.h"
#include "regscan/matchers/i_matcher_factory.h"
#include "regscan/matchers/i_search_file_buf.h"
#include "regscan/matchers/i_search_in_file_buf_list.h"
#include "regscan/matchers/matchers_logger.h"
#include "regscan/memory_loader/file_buf.h"

class UcSearchInFileBufList : private MatchersLogger, public ISearchInFileBufList {
 public:
  UcSearchInFileBufList(ISearchFileBuf& search_file_buf_uc);

  void Search(IMatcher& matcher, const file_buf_list& fblist) override;

 private:
  ISearchFileBuf& search_file_buf_uc_;
};
