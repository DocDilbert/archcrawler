#pragma once

#include "regscan/matchers/match.h"

struct MatchInFile {
  std::string filename;
  Match match;
};
