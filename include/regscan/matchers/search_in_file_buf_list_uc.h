#pragma once
#include <memory>

#include "regscan/matchers/i_matcher_factory.h"
#include "regscan/matchers/matchers_logger.h"
#include "regscan/matchers/search_file_buf_uc.h"
#include "regscan/memory_loader/file_buf.h"

class SearchInFileBufListUc : private MatchersLogger {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  typedef std::vector<file_buf_ptr> file_buf_list;

  SearchInFileBufListUc();

  void Search(SearchFileBufUc& search_fbuf_uc, file_buf_list& fblist);

 private:
};
