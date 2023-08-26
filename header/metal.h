#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal : public material
{
private:
  color albedo_;

public:
  metal(const color &c) : albedo_(c) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    vec3 reflect_dir = reflect(rec.normal(), in_ray.direction());
    scattered_ray = ray(rec.p(), reflect_dir);
    attenuation = albedo_;
    return true;
  }
};

#endif