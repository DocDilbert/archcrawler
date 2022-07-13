#pragma once
#include <memory>

#include "archcrawler/matchers/i_iter.h"
#include "archcrawler/matchers/match_group.h"

class IMatcher {
 public:
  virtual ~IMatcher(){};
  virtual std::unique_ptr<IIter<MatchGroup>> Search(const char* subject) = 0;
};