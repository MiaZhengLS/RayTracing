#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal : public material
{
private:
  color albedo_;
  double fuzz_;

public:
  metal(const color &c, const double fuzz) : albedo_(c), fuzz_(fuzz < 1 ? fuzz : 1) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    vec3 reflect_dir = reflect(rec.normal(), in_ray.direction());
    scattered_ray = ray(rec.p(), reflect_dir + random_unit_vector() * fuzz_);
    attenuation = albedo_;
    return dot(scattered_ray.direction(), rec.normal()) > 0;
  }
};

#endif