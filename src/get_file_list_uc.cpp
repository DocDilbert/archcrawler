#include "regscan/get_file_list_uc.h"

#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include <iostream>

GetFileListUseCase::GetFileListUseCase(IListDirService& list_dir_service) : list_dir_service_(list_dir_service) {}

GetFileListUseCase::str_vector GetFileListUseCase::GetFileList(std::string path, str_vector allowed_extensions) {
  spdlog::stopwatch sw;
  spdlog::info("GetFileListUseCase::GetFileList({})", path);
  auto ret = GetFileListFromDir(path, allowed_extensions);
  spdlog::debug("GetFileListUseCase::GetFileList elapsed={:.3}", sw);
  return ret;
}

GetFileListUseCase::str_vector GetFileListUseCase::GetFileListFromDir(std::string path, const str_vector& allowed_extensions) {
  str_vector ret;
  auto dirlist = list_dir_service_.ListDir(path);
  for (auto const& file_and_path : dirlist) {
    if (file_and_path.is_dir) {
      auto res_dir = GetFileListFromDir(file_and_path.fullpath, allowed_extensions);
      ret.insert(ret.end(), res_dir.begin(), res_dir.end());
    } else if (file_and_path.is_file) {
      ret.push_back(file_and_path.fullpath);
    }
  }
  return ret;
}
