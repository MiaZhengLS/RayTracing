#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "vec3.h"
class dielectric : public material
{
private:
  double index_refraction_;

public:
  dielectric(double index_refraction) : index_refraction_(index_refraction < 1 ? 1 : index_refraction) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    attenuation = color(1, 1, 1);
    double eta_ratio = rec.is_front_face() ? 1.0 / index_refraction_ : index_refraction_;
    vec3 refract_dir = refract(rec.normal(), unit_vector(in_ray.direction()), eta_ratio);
    scattered_ray = ray(rec.p(), refract_dir);
    return true;
  }
};

#endif