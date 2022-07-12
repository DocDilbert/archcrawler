#pragma once

#include "regscan/matchers/i_create_abstract_matcher.h"
#include "regscan/matchers/i_search_in_file_buf_list.h"
#include "regscan/matchers/matchers_logger.h"
#include "regscan/memory_loader/file_buf.h"

class UcSearchRegexInFilebufList : public MatchersLogger {
 public:
  typedef std::unique_ptr<FileBuf> file_buf_ptr;
  typedef std::vector<file_buf_ptr> file_buf_list;

  UcSearchRegexInFilebufList(ICreateAbstractMatcherUc& i_create_abstract_matcher, ISearchInFileBufList& i_search_in_file_buf_list);

  void Do(std::string pattern, const file_buf_list& fbufs);

 private:
  ICreateAbstractMatcherUc& i_create_abstract_matcher_;
  ISearchInFileBufList& i_search_in_file_buf_list_;
};
