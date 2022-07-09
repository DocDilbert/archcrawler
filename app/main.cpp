#include <fmt/core.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include <stdio.h>

#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>

#include "app_config.h"
#include "list_dir_fs_service.h"
#include "load_file_fs_service.h"
#include "regscan/file_list/file_extension_whitelist_uc.h"
#include "regscan/file_list/get_file_list_uc.h"
#include "regscan/file_list/path_beginswith_blacklist_uc.h"
#include "regscan/file_list/path_contains_blacklist_uc.h"
#include "regscan/memory_loader/load_filelist_uc.h"
#include "regscan/regscan_config.h"

#define PCRE2_CODE_UNIT_WIDTH 8
#include "pcre2.h"

void PrintCppStandard() {
  if (__cplusplus == 201703L)
    std::cout << "C++17\n";
  else if (__cplusplus == 201402L)
    std::cout << "C++14\n";
  else if (__cplusplus == 201103L)
    std::cout << "C++11\n";
  else if (__cplusplus == 199711L)
    std::cout << "C++98\n";
  else
    std::cout << "pre-standard C++\n";
}

int main(int argc, const char* argv[]) {
  cxxopts::Options options("MyProgram", "One line description of MyProgram");

  // clang-format off
  options.add_options()
    ("l,filelist", "Print out file list to be read") // a bool parameter
    ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage")
    ;
  // clang-format on

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const cxxopts::OptionParseException& x) {
    std::cerr << "dog: " << x.what() << '\n';
    std::cerr << "usage: dog [options] <input_file> ...\n";
    return EXIT_FAILURE;
  }
  PrintCppStandard();

  // print out help if necessary
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  auto app_logger = spdlog::stdout_color_mt(app_logger_name);
  auto regscan_file_list_logger = spdlog::stdout_color_mt(regscan_file_list_logger_name);
  auto regscan_memory_loader_logger = spdlog::stdout_color_mt(regscan_memory_loader_logger_name);
  // Enable logging
  switch (result.count("verbose")) {
    case 0:
      spdlog::set_level(spdlog::level::off);
      break;
    case 1:
      spdlog::set_level(spdlog::level::info);
      break;
    case 2:
      spdlog::set_level(spdlog::level::debug);
      break;
    default:
      spdlog::set_level(spdlog::level::trace);
      break;
  }

  regscan_file_list_logger->set_level(spdlog::level::off);
  app_logger->set_level(spdlog::level::off);

  spdlog::info("Collecting a list of files to be loaded.");
  std::vector<std::shared_ptr<IDirEntryPredicate>> dir_entry_predicates;

  std::vector<std::string> beginswith_blacklist = {".\\.git", ".\\tools", ".\\doc", ".\\libs"};
  dir_entry_predicates.push_back(std::make_unique<PathBeginswithBlacklistUc>(beginswith_blacklist));

  std::vector<std::string> contains_blacklist = {"__pycache__"};
  dir_entry_predicates.push_back(std::make_unique<PathContainsBlacklistUc>(contains_blacklist));

  std::vector<std::string> extension_whitelist = {".cpp", ".h"};
  dir_entry_predicates.push_back(std::make_unique<FileExtensionWhitelistUc>(extension_whitelist));

  ListDirFsService list_dir_service;
  GetFileListUseCase get_file_list_uc(list_dir_service, dir_entry_predicates);

  auto file_list = get_file_list_uc.GetFileList(".");
  spdlog::info("Collected a list of {} filenames", file_list.size());

  LoadFileFsService load_file_fs_service;
  LoadFileListUc load_file_list_uc(load_file_fs_service);
  load_file_list_uc.Load(file_list);

  if (result.count("filelist")) {
    // print out filelist
    for (auto const& i : file_list) {
      std::cout << i << "\n";
    }
  }

  pcre2_code* re;
  PCRE2_SPTR pattern; /* PCRE2_SPTR is a pointer to unsigned code units of */
  PCRE2_SPTR name_table;

  int crlf_is_newline;
  int errornumber;
  int find_all;
  int i;
  int namecount;
  int name_entry_size;
  int rc;
  int utf8;

  uint32_t option_bits;
  uint32_t newline;

  PCRE2_SIZE erroroffset;
  PCRE2_SIZE* ovector;

  pcre2_match_data* match_data;
  pattern = (PCRE2_SPTR) "HELLO";
  re = pcre2_compile(pattern,               /* the pattern */
                     PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
                     0,                     /* default options */
                     &errornumber,          /* for error number */
                     &erroroffset,          /* for error offset */
                     NULL);                 /* use default compile context */
  if (re == NULL) {
    PCRE2_UCHAR buffer[256];
    pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
    printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
    return 1;
  }

  auto subject = (PCRE2_SPTR) "ABC HELLO WORLD";
  auto subject_length = strlen((char*)subject);
  match_data = pcre2_match_data_create_from_pattern(re, NULL);
  rc = pcre2_match(re,             /* the compiled pattern */
                   subject,        /* the subject string */
                   subject_length, /* the length of the subject */
                   0,              /* start at offset 0 in the subject */
                   0,              /* default options */
                   match_data,     /* block for storing the result */
                   NULL);          /* use default match context */

  if (rc < 0) {
    switch (rc) {
      case PCRE2_ERROR_NOMATCH:
        printf("No match\n");
        break;
      /*
      Handle other special cases if you like
      */
      default:
        printf("Matching error %d\n", rc);
        break;
    }
    pcre2_match_data_free(match_data); /* Release memory used for the match */
    pcre2_code_free(re);               /* data and the compiled pattern. */
    return 1;
  }

  /* Match succeded. Get a pointer to the output vector, where string offsets are
  stored. */

  ovector = pcre2_get_ovector_pointer(match_data);
  /* The output vector wasn't big enough. This should not happen, because we used
  pcre2_match_data_create_from_pattern() above. */

  printf("\nMatch succeeded at offset %d\n", (int)ovector[0]);
  if (rc == 0) printf("ovector was not big enough for all the captured substrings\n");

  /* Show substrings stored in the output vector by number. Obviously, in a real
  application you might want to do things other than print them. */

  for (i = 0; i < rc; i++) {
    PCRE2_SPTR substring_start = subject + ovector[2 * i];
    size_t substring_length = ovector[2 * i + 1] - ovector[2 * i];
    printf("%2d: %.*s\n", i, (int)substring_length, (char*)substring_start);
  }
  pcre2_match_data_free(match_data);
  pcre2_code_free(re);
}
