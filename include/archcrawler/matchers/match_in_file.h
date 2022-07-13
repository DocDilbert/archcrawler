#pragma once

#include <string>

#include "archcrawler/matchers/match.h"

struct MatchInFile {
  std::string filename;
  Match match;
};
