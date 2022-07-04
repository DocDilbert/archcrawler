#include <fmt/core.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>
#include <stdio.h>

#include <cxxopts.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>

#include "list_dir_fs_service.h"
#include "regscan/get_file_list_uc.h"

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

  ListDirFsService list_dir_service;

  GetFileListUseCase get_file_list_uc(list_dir_service);

  std::vector<std::string> allowed_extensions;
  auto file_list = get_file_list_uc.GetFileList(".", allowed_extensions);

  if (result.count("filelist")) {
    // print out filelist
    for (auto const& i : file_list) {
      std::cout << i << "\n";
    }
  }
}
