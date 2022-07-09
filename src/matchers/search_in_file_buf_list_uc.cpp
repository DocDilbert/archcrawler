#include "regscan/matchers/search_in_file_buf_list_uc.h"

SearchInFileBufListUc::SearchInFileBufListUc() : MatchersLogger() {}

void SearchInFileBufListUc::Search(SearchFileBufUc& search_fbuf_uc, file_buf_list& fblist) {
  for (auto& fb : fblist) {
    auto iter = search_fbuf_uc.Search(fb);

    if (iter->IsDone()) {
      logger_->debug("No match");
    }
    int i = 0;
    char* subject = fb->GetBufferPtr();
    for (; !iter->IsDone(); iter->Next()) {
      auto match = iter->Current();
      char* substring_start = (char*)subject + match.begin_pos;

      auto match_str = std::string(substring_start, match.length);
      logger_->debug("{}: {} - {}", i, match.begin_pos, match_str);
      i++;
    }
  }
}
