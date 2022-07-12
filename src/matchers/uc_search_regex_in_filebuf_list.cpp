#include "regscan/matchers/uc_search_regex_in_filebuf_list.h"

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

UcSearchRegexInFilebufList::UcSearchRegexInFilebufList(ICreateAbstractMatcherUc& i_create_abstract_matcher, ISearchInFileBufList& i_search_in_file_buf_list)
    : MatchersLogger(), i_create_abstract_matcher_(i_create_abstract_matcher), i_search_in_file_buf_list_(i_search_in_file_buf_list) {}

void UcSearchRegexInFilebufList::Do(std::string pattern, const file_buf_list& fbufs) {
  spdlog::stopwatch sw;
  // Create a matcher for regular expressions
  auto matcher = i_create_abstract_matcher_.Create("regex", pattern);

  // Search
  auto iter = i_search_in_file_buf_list_.Search(*matcher, fbufs);

  int matches = 0;
  for (; !iter->IsDone(); iter->Next()) {
    auto match_in_file = iter->Current();
    auto match = match_in_file.match;
    logger_->trace("{}: {} - {}", match_in_file.filename, match.begin_pos, match.end_pos);
    matches++;
  }

  logger_->debug("UcSearchRegexInFilebufList::Do(pattern=\"{}\") found {} occurrences of pattern. This took {:.3}", pattern, matches, sw);
}
