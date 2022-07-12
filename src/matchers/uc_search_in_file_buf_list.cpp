#include "regscan/matchers/uc_search_in_file_buf_list.h"

#include <memory>

class MatchIter : public IIter<Match> {
 public:
  typedef UcSearchInFileBufList::file_buf_list file_buf_list;
  typedef file_buf_list::const_iterator file_buf_iter;

  MatchIter(ISearchFileBuf& search_file_buf, IMatcher& matcher, const file_buf_list& fblist)
      : search_file_buf_(search_file_buf), matcher_(matcher), fblist_(fblist) {
    fit = fblist.cbegin();
    fend = fblist.cend();

    auto& fb = *fit;
    mfbuf_iter_ = search_file_buf_.Search(matcher, fb);
    //
  }
  virtual ~MatchIter() {}
  bool IsDone() override {
    if (fit == fend) {
      return true;
    }

    return false;
  }
  void Next() override {}

  Match Current() override { return Match(); }

 private:
  ISearchFileBuf& search_file_buf_;
  IMatcher& matcher_;
  const UcSearchInFileBufList::file_buf_list& fblist_;
  file_buf_iter fit;
  file_buf_iter fend;
  std::unique_ptr<IIter<Match>> mfbuf_iter_;
};

UcSearchInFileBufList::UcSearchInFileBufList(ISearchFileBuf& search_file_buf_uc) : MatchersLogger(), search_file_buf_uc_(search_file_buf_uc) {}

void UcSearchInFileBufList::Search(IMatcher& matcher, const file_buf_list& fblist) {
  auto iter = std::make_unique<MatchIter>(search_file_buf_uc_, matcher, fblist);
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
