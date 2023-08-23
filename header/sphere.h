#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
private:
  point3 center_;
  double radius_;

public:
  sphere(const point3 &center, const double radius) : center_(center), radius_(radius) {}
  ~sphere() {}
  bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const override;
};

#endif
