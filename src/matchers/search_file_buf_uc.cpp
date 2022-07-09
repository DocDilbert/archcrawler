#include "regscan/matchers/search_file_buf_uc.h"

SearchFileBufUc::SearchFileBufUc(std::unique_ptr<IMatcher> matcher) : MatchersLogger(), matcher_(std::move(matcher)) {}

std::unique_ptr<IMatchIter> SearchFileBufUc::Search(const file_buf_ptr& file_buf) {
  logger_->debug("SearchFileBufUc::Search filename={}", file_buf->GetFilename());
  auto iter = matcher_->Search(file_buf->GetBufferPtr());
  return iter;
}
