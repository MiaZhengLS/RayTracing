#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class lambertian : public material
{
private:
  color albedo_;

public:
  lambertian(const color &c) : albedo_(c) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    vec3 scatter_dir = rec.normal() + random_on_hemisphere(rec.normal());
    // Avoid infinities / NaNs
    if (scatter_dir.near_zero())
    {
      scatter_dir = rec.normal();
    }
    scattered_ray = ray(rec.p(), scatter_dir);
    attenuation = albedo_;
    return true;
  }
};

#endif