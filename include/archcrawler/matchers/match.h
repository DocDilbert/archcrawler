#pragma once

#include <vector>

#include "archcrawler/matchers/match_group.h"

struct Match {
  std::vector<MatchGroup> groups;
};
