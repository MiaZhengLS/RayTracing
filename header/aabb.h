#ifndef AABB_H
#define AABB_H

#include "common.h"

class aabb
{
private:
  interval interval_x_;
  interval interval_y_;
  interval interval_z_;

public:
  aabb() {}
  aabb(const interval interval_x, const interval interval_y, const interval interval_z) : interval_x_(interval_x), interval_y_(interval_y), interval_z_(interval_z) {}
  aabb(const point3 a, const point3 b)
  {
    interval_x_ = interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
    interval_y_ = interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
    interval_z_ = interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
  }
  aabb(const aabb &a, const aabb &b)
  {
    interval_x_ = interval(a.axis(0), b.axis(0));
    interval_y_ = interval(a.axis(1), b.axis(1));
    interval_z_ = interval(a.axis(2), b.axis(2));
  }

  const interval &axis(int idx) const
  {
    return (idx == 0 ? interval_x_ : (idx == 1 ? interval_y_ : interval_z_));
  }

  bool hit(const ray &r, const interval &r_interval) const
  {
    double overlap_min = r_interval.min();
    double overlap_max = r_interval.max();
    for (int i = 0; i < 3; ++i)
    {
      // Handle "divided by zero" with IEEE 754 floating-point number
      // https://en.wikipedia.org/wiki/IEEE_754#:~:text=Many%20hardware%20floating%2Dpoint%20units,a%20number%22%20values%20(NaNs)
      // Simply put, we don't need to manually handle it
      // If denominator is 0 and nominator is not, we get +infinity/-infinity based on the sign of nominator
      // If nominator is also 0, we get NaNs(not a number values)
      const double inv_dir = 1.0 / r.direction()[i];
      double t0 = (axis(i).min() - r.origin()[i]) * inv_dir;
      double t1 = (axis(i).max() - r.origin()[i]) * inv_dir;
      if (inv_dir < 0)
      {
        std::swap(t0, t1);
      }
      if (t0 > overlap_min)
        overlap_min = t0;
      if (t1 < overlap_max)
        overlap_max = t1;
      if (overlap_min >= overlap_max)
      {
        return false;
      }
    }
    return true;
  }
};

#endif