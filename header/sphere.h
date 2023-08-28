#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"
#include "aabb.h"

class sphere : public hittable
{
private:
  point3 center_;
  double radius_;
  shared_ptr<material> mat_;
  aabb bounding_box_;

public:
  sphere(const point3 center, const double radius, shared_ptr<material> mat) : center_(center), radius_(radius), mat_(mat)
  {
    const vec3 r_vec = vec3(radius, radius, radius);
    bounding_box_ = aabb(center - r_vec, center + r_vec);
  }
  ~sphere() {}
  bool hit(const ray &r, const interval &ray_interval, hit_record &rec) const override;
  aabb bounding_box() const override { return bounding_box_; }
};

#endif
