#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"

class sphere : public hittable
{
private:
  point3 center_;
  double radius_;
  shared_ptr<material> mat_;

public:
  sphere(const point3 &center, const double radius, shared_ptr<material> mat) : center_(center), radius_(radius), mat_(mat) {}
  ~sphere() {}
  bool hit(const ray &r, const interval &ray_interval, hit_record &rec) const override;
};

#endif
