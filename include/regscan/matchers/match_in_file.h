#pragma once

#include <string>
#include "regscan/matchers/match_group.h"

struct MatchInFile {
  std::string filename;
  MatchGroup match_group;
};
