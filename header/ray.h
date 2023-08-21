#ifndef RAY_H
#define RAY_H

#include "vec3.h"

using point3 = vec3;

class ray
{
public:
  ray() {}
  ray(const point3 &orig, const vec3 &dir) : origin_(orig), direction_(dir) {}
  point3 origin() const { return origin_; }
  vec3 direction() const { return direction_; }
  point3 at(double t) const { return origin_ + t * direction_; }

private:
  point3 origin_;
  vec3 direction_;
};

#endif