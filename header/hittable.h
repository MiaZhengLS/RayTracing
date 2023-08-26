#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.h"

class material;

class hit_record
{
private:
  point3 p_;
  vec3 normal_;
  double t_;
  bool is_front_face_;
  shared_ptr<material> mat_;

public:
  void set_record(const point3 &p, double t, const vec3 &outward_normal, const vec3 &ray_dir, const shared_ptr<material> &mat)
  {
    p_ = p;
    t_ = t;
    // If ray intersects the object from outside, the outward_normal points against the direction of the ray
    // If ray intersects the object from inside, the outward_normal points similar direction with the ray
    is_front_face_ = dot(ray_dir, outward_normal) < 0;
    normal_ = is_front_face_ ? outward_normal : -outward_normal;
    mat_ = mat;
  }
  vec3 normal() const { return normal_; }
  double t() const { return t_; }
  vec3 p() const { return p_; }
  shared_ptr<material> mat() const { return mat_; }
};

class hittable
{
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, const interval &ray_interval, hit_record &rec) const = 0;
};

#endif
