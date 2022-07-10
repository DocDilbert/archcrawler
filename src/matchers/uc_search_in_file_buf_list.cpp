#include "regscan/matchers/uc_search_in_file_buf_list.h"

UcSearchInFileBufList::UcSearchInFileBufList(ISearchFileBuf& search_file_buf_uc) : MatchersLogger(), search_file_buf_uc_(search_file_buf_uc) {}

void UcSearchInFileBufList::Search(IMatcher& matcher, const file_buf_list& fblist) {
  for (auto& fb : fblist) {
    auto iter = search_file_buf_uc_.Search(matcher, fb);

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
