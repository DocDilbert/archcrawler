#include "regscan/matchers/uc_search_file_buf.h"

SearchFileBufUc::SearchFileBufUc() : MatchersLogger() {}

std::unique_ptr<IMatchIter> SearchFileBufUc::Search(IMatcher& matcher, const file_buf_ptr& file_buf) {
  logger_->debug("SearchFileBufUc::Search filename={}", file_buf->GetFilename());
  auto iter = matcher.Search(file_buf->GetBufferPtr());
  return iter;
}
