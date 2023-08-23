#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class interval
{
private:
  double min_;
  double max_;

public:
  interval() : min_(+infinity), max_(-infinity) {}
  interval(double min, double max) : min_(min), max_(max) {}
  bool contains(double x) const { return x <= max_ && x >= min_; }
  bool surrounds(double x) const { return x < max_ && x > min_; }
  double max() const { return max_; }
  double min() const { return min_; }
  static const interval empty, universe;
};

#endif
