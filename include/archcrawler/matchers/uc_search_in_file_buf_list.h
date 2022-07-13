#pragma once
#include <memory>

#include "archcrawler/matchers/i_matcher.h"
#include "archcrawler/matchers/i_matcher_factory.h"
#include "archcrawler/matchers/i_search_file_buf.h"
#include "archcrawler/matchers/i_search_in_file_buf_list.h"
#include "archcrawler/matchers/matchers_logger.h"
#include "archcrawler/memory_loader/file_buf.h"

class UcSearchInFileBufList : private MatchersLogger, public ISearchInFileBufList {
 public:
  UcSearchInFileBufList(ISearchFileBuf& search_file_buf_uc);

  std::unique_ptr<IIter<MatchInFile>> Search(IMatcher& matcher, const file_buf_list& fblist) override;

 private:
  ISearchFileBuf& search_file_buf_uc_;
};
