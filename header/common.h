#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <memory>
#include <cstdlib>

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

inline double random_double(){
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
  return min + (max - min) * random_double();
}

#endif
