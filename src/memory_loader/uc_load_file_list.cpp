#include "regscan/memory_loader/uc_load_file_list.h"

#include <spdlog/stopwatch.h>

UcLoadFileList::UcLoadFileList(ILoadFileService& load_file_service) : MemoryLoaderLogger(), load_file_service_(load_file_service) {}

UcLoadFileList::file_buf_list UcLoadFileList::Load(str_vector fname_list) {
  spdlog::stopwatch sw;
  logger_->info("UcLoadFileList::Load - Loading {} files to memory ...", fname_list.size());
  file_buf_list re;
  long used_memory = 0;
  for (auto& i : fname_list) {
    std::unique_ptr<FileBuf> file_buf = load_file_service_.LoadFile(i);
    used_memory += file_buf->GetBufferSize();
    re.push_back(std::move(file_buf));
  }

  logger_->debug("UcLoadFileList::Load elapsed={:.3}, Memory allocated = {} bytes", sw, used_memory);
  return re;
}
