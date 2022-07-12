#pragma once

#include <string>
#include "regscan/matchers/match.h"

struct MatchInFile {
  std::string filename;
  Match match;
};
