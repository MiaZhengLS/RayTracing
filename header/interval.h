#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>
#include "common.h"

const double infinity = std::numeric_limits<double>::infinity();

class interval
{
private:
  double min_;
  double max_;

public:
  interval() : min_(+infinity), max_(-infinity) {}
  interval(double min, double max) : min_(min), max_(max) {}
  interval(const interval &a, const interval &b) : min_(fmin(a.min(), b.min())), max_(fmax(a.max(), b.max())) {}
  bool contains(double x) const { return x <= max_ && x >= min_; }
  bool surrounds(double x) const { return x < max_ && x > min_; }
  double clamp(double x) const
  {
    if (x < min_)
      return min_;
    if (x > max_)
      return max_;
    return x;
  }
  double max() const { return max_; }
  double min() const { return min_; }
  static const interval empty, universe;
};

#endif
