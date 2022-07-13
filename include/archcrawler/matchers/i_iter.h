#pragma once

template <class T>
class IIter {
 public:
  virtual ~IIter() {}
  virtual void Next() = 0;
  virtual T Current() = 0;
  virtual bool IsDone() = 0;
};
