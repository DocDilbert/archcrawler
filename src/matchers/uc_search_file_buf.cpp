#include "regscan/matchers/uc_search_file_buf.h"

UcSearchFileBuf::UcSearchFileBuf() : MatchersLogger() {}

std::unique_ptr<IMatchIter> UcSearchFileBuf::Search(IMatcher& matcher, const file_buf_ptr& file_buf) {
  logger_->debug("UcSearchFileBuf::Search filename={}", file_buf->GetFilename());
  auto iter = matcher.Search(file_buf->GetBufferPtr());
  return iter;
}
