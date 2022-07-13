#pragma once

#include <vector>

#include "regscan/matchers/match_group.h"

struct Match {
  std::vector<MatchGroup> groups;
};
