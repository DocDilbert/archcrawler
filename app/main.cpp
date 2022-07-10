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
#include "regex.h"
#include "regscan/file_list/file_extension_whitelist_uc.h"
#include "regscan/file_list/get_file_list_uc.h"
#include "regscan/file_list/path_beginswith_blacklist_uc.h"
#include "regscan/file_list/path_contains_blacklist_uc.h"
#include "regscan/matchers/create_abstract_matcher_uc.h"
#include "regscan/matchers/i_register_matcher_factory_uc.h"
#include "regscan/matchers/matcher_factory_registry.h"
#include "regscan/matchers/register_matcher_factory_uc.h"
#include "regscan/matchers/uc_search_file_buf.h"
#include "regscan/matchers/uc_search_in_file_buf_list.h"
#include "regscan/matchers/uc_search_regex_in_filebuf_list.h"
#include "regscan/memory_loader/load_file_list_uc.h"
#include "regscan/regscan_config.h"

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
  auto regscan_matchers_logger = spdlog::stdout_color_mt(regscan_matchers_logger_name);

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
  auto file_buf_list = load_file_list_uc.Load(file_list);

  // print out filelist
  if (result.count("filelist")) {
    for (auto const& i : file_list) {
      std::cout << i << "\n";
    }
  }
  try {
    MatcherFactoryRegistry matcher_factory_registry;
    RegisterMatcherFactoryUc register_matcher_factory_uc(matcher_factory_registry);
    register_matcher_factory_uc.Register("regex", std::make_unique<RegexFactory>());
    CreateAbstractMatcherUc create_abstract_matcher_uc(matcher_factory_registry);

    RegexFactory regex_fac;
    SearchFileBufUc search_file_buf_uc;
    SearchInFileBufListUc search_in_file_buf_list(search_file_buf_uc);

    UcSearchRegexInFilebufList search_regex_in_fbufs(create_abstract_matcher_uc, search_in_file_buf_list);
    search_regex_in_fbufs.Do("PCRE2", file_buf_list);

  } catch (RegexCompileException& ex) {
    spdlog::error("PCRE2 compilation failed at offset {}:{} \n", ex.error_offset, ex.error_message);
  }
}
