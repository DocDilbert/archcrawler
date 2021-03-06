#include "regscan/memory_loader/load_filelist_uc.h"

#include <spdlog/stopwatch.h>

LoadFileListUc::LoadFileListUc(ILoadFileService& load_file_service) : MemoryLoaderLogger(), load_file_service_(load_file_service) {}

LoadFileListUc::file_list LoadFileListUc::Load(str_vector fname_list) {
  spdlog::stopwatch sw;
  logger_->info("LoadFileListUc::Load - Loading {} files to memory ...", fname_list.size());
  file_list re;
  long used_memory = 0;
  for (auto& i : fname_list) {
    std::shared_ptr<FileBuf> file_buf = load_file_service_.LoadFile(i);
    used_memory += file_buf->GetBufferSize();
    re.push_back(file_buf);
  }

  logger_->debug("LoadFileListUc::Load elapsed={:.3}, Memory allocated = {} bytes", sw, used_memory);
  return re;
}
