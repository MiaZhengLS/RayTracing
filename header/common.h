#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>

#include "ray.h"
#include "interval.h"

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double pi = 3.1415926535897932385;

inline double degree_to_radian(double degree)
{
  return degree * pi / 180.0;
}

#endif
