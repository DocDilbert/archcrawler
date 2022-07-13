#include "archcrawler/matchers/uc_search_file_buf.h"

#include "archcrawler/matchers/match.h"

class SingleMatchIter : public IIter<Match> {
 public:
  SingleMatchIter(IMatcher& matcher, const UcSearchFileBuf::file_buf_ptr& file_buf) : matcher_(matcher), file_buf_(file_buf), iter_done_(false) {
    match_group_iter_ = matcher_.Search(file_buf->GetBufferPtr());
    if (match_group_iter_->IsDone()) {
      iter_done_ = true;
    }
  }
  virtual ~SingleMatchIter() {}

  std::vector<MatchGroup> ReadMatchGroups(IIter<MatchGroup>& iter_matcher_group) {
    std::vector<MatchGroup> groups;
    for (; !iter_matcher_group.IsDone(); iter_matcher_group.Next()) {
      groups.push_back(iter_matcher_group.Current());
    }
    return groups;
  }

  bool IsDone() override { return iter_done_; }

  void Next() override { iter_done_ = true; }

  Match Current() override {
    Match match;
    if (iter_done_ == false) {
      match.groups = ReadMatchGroups(*match_group_iter_);
    }
    return match;
  }

 private:
  IMatcher& matcher_;
  const UcSearchFileBuf::file_buf_ptr& file_buf_;
  std::unique_ptr<IIter<MatchGroup>> match_group_iter_;
  bool iter_done_;
};

UcSearchFileBuf::UcSearchFileBuf() : MatchersLogger() {}

std::unique_ptr<IIter<Match>> UcSearchFileBuf::Search(IMatcher& matcher, const file_buf_ptr& file_buf) {
  logger_->trace("UcSearchFileBuf::Search(filename={})", file_buf->GetFilename());
  auto iter = std::make_unique<SingleMatchIter>(matcher, file_buf);
  return iter;
}
