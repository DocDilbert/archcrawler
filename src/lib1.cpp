#include "lib1/lib1.hpp"

#include <fmt/core.h>
#include <spdlog/spdlog.h>

void Lib1::PrintMessage() {
  spdlog::info("Welcome to lib1");
  fmt::print("Hello Library with Fmt\n");
}

