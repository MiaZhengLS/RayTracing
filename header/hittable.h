#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record
{
private:
  point3 p_;
  vec3 normal_;
  double t_;
  bool is_front_face_;

public:
  void set_record(const point3 p, double t, vec3 outward_normal, vec3 ray_dir)
  {
    p_ = p;
    t_ = t;
    is_front_face_ = dot(ray_dir, outward_normal);
    normal_ = is_front_face_ ? outward_normal : -outward_normal;
  }
  vec3 normal() const { return normal_; }
};

class hittable
{
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, const double ray_tmin, const double ray_tmax, hit_record &rec) const = 0;
};

#endif
