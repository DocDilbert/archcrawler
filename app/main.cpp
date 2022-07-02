#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <stdio.h>

#include <cxxopts.hpp>
#include <iostream>
#include <typeinfo>

#include "lib1/lib1.hpp"

void PrintHelloWorld() {
  int dec = 5;
  fmt::print("Hello, world {}!\n", dec);
}
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

void Test() {
  PrintHelloWorld();
  Lib1 lib1;
  lib1.PrintMessage();
  PrintCppStandard();
}

int main(int argc, const char* argv[]) {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);
  cxxopts::Options options("MyProgram", "One line description of MyProgram");

  // clang-format off
  options.add_options()
    ("d,debug", "Enable debugging") // a bool parameter
    ("t,test", "Test case") // a bool parameter
    ("f,file", "File name", cxxopts::value<std::string>())
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

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (result.count("test")) {
    Test();
  }
}
