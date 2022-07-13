#include "archcrawler/matchers/uc_search_in_file_buf_list.h"

#include <fmt/core.h>

#include <memory>

class MatchInFileIter : public IIter<MatchInFile> {
 public:
  typedef UcSearchInFileBufList::file_buf_list file_buf_list;
  typedef file_buf_list::const_iterator file_buf_iter;

  MatchInFileIter(ISearchFileBuf& search_file_buf, IMatcher& matcher, const file_buf_list& fblist) : search_file_buf_(search_file_buf), matcher_(matcher) {
    fit_ = fblist.cbegin();
    fend_ = fblist.cend();

    auto& fb = *fit_;
    mfbuf_iter_ = search_file_buf_.Search(matcher, fb);
    Advance_iterators(false);
  }

  void Advance_iterators(bool next_match_iter) {
    if (next_match_iter) {
      mfbuf_iter_->Next();  // Next buffer entry
    }
    while (mfbuf_iter_->IsDone()) {
      fit_++;
      if (fit_ == fend_) {
        return;  // finish when buf list was exhausted
      }
      auto& fb = *fit_;
      mfbuf_iter_ = search_file_buf_.Search(matcher_, fb);
    }
  }

  virtual ~MatchInFileIter() {}

  bool IsDone() override { return (fit_ == fend_); }

  void Next() override { Advance_iterators(true); }

  MatchInFile Current() override {
    auto& fb = *fit_;
    MatchInFile match_in_file;

    match_in_file.filename = fb->GetFilename();
    match_in_file.match = mfbuf_iter_->Current();

    return match_in_file;
  }

 private:
  ISearchFileBuf& search_file_buf_;
  IMatcher& matcher_;
  file_buf_iter fit_;
  file_buf_iter fend_;
  std::unique_ptr<IIter<Match>> mfbuf_iter_;
};

UcSearchInFileBufList::UcSearchInFileBufList(ISearchFileBuf& search_file_buf_uc) : MatchersLogger(), search_file_buf_uc_(search_file_buf_uc) {}

std::unique_ptr<IIter<MatchInFile>> UcSearchInFileBufList::Search(IMatcher& matcher, const file_buf_list& fblist) {
  auto iter = std::make_unique<MatchInFileIter>(search_file_buf_uc_, matcher, fblist);
  return iter;
}
