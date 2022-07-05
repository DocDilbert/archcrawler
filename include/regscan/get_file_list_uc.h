#pragma once

#include <string>
#include <vector>

#include "regscan/i_list_dir_service.h"

class GetFileListUseCase {
 public:
  typedef std::vector<std::string> str_vector;
  GetFileListUseCase(IListDirService& list_dir_service);

  str_vector GetFileList(std::string path, str_vector extensions);

 private:
  str_vector GetFileListFromDir(std::string path, const str_vector& extensions);
  IListDirService& list_dir_service_;
};

