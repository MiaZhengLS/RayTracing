#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>

#include "ray.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degree_to_radian(double degree)
{
  return degree * pi / 180.0;
}

#endif
