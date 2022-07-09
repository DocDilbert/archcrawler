
#pragma once

#include <fcntl.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "app_config.h"
#include "regscan/memory_loader/file_buf.h"
#include "regscan/memory_loader/i_load_file_service.h"

#ifndef _MSC_VER
errno_t fopen_s(FILE **f, const char *name, const char *mode) {
  errno_t ret = 0;
  assert(f);
  *f = fopen(name, mode);
  /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
  if (!*f) ret = errno;
  return ret;
}
#endif

class LoadFileFsService : public ILoadFileService {
 public:
  LoadFileFsService() { logger_ = spdlog::get(app_logger_name); }

  std::unique_ptr<FileBuf> LoadFile(std::string fname) override {
    FILE *fp;
    auto err = fopen_s(&fp, fname.c_str(), "r");
    if (err != 0) {
      // handle error
      //  return nullptr;
    }
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET); /* same as rewind(f); */

    auto file = std::make_unique<FileBuf>(fname, fsize);
    fread(file->GetBufferPtr(), fsize + 1, 1, fp);  // +1 because of null termination
    fclose(fp);

    return file;
  }

 private:
  std::shared_ptr<spdlog::logger> logger_;
};
