#pragma once
#include <memory>

#include "archcrawler/matchers/i_iter.h"
#include "archcrawler/matchers/i_matcher.h"
#include "archcrawler/matchers/i_search_file_buf.h"
#include "archcrawler/matchers/match.h"
#include "archcrawler/matchers/matchers_logger.h"
#include "archcrawler/memory_loader/file_buf.h"

class UcSearchFileBuf : private MatchersLogger, public ISearchFileBuf {
 public:
  UcSearchFileBuf();

  std::unique_ptr<IIter<Match>> Search(IMatcher& matcher, const file_buf_ptr& file_buf) override;

 private:
};
