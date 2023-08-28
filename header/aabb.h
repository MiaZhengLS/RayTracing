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
  aabb(const interval &interval_x, const interval &interval_y, const interval &interval_z) : interval_x_(interval_x), interval_y_(interval_y), interval_z_(interval_z) {}
  aabb(const point3 &a, const point3 &b)
  {
    interval_x_ = interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
    interval_y_ = interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
    interval_z_ = interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
  }

  const interval &axis(int idx) const
  {
    return (idx == 0 ? interval_x_ : (idx == 1 ? interval_y_ : interval_z_));
  }

  bool hit(const ray &r, const interval &r_interval)
  {
    double overlap_min = r_interval.min();
    double overlap_max = r_interval.max();
    for (int i = 0; i < 3; ++i)
    {
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