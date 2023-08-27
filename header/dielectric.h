#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "vec3.h"
class dielectric : public material
{
private:
  double refraction_index_;

public:
  dielectric(double refraction_index) : refraction_index_(refraction_index < 1 ? 1 : refraction_index) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    attenuation = color(1, 1, 1);
    double eta_ratio = rec.is_front_face() ? 1.0 / refraction_index_ : refraction_index_;
    double cos_theta = dot(unit_vector(in_ray.direction()), rec.normal());
    double sin_theta = sqrt(1 - cos_theta * cos_theta);
    vec3 scattered_dir;
    // Internal total reflection 
    // https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
    // sin(theta') = sin(theta) * eta_ratio
    // Invalid sin value -> no refraction
    if (eta_ratio * sin_theta > 1.0)
    {
      scattered_dir = reflect(rec.normal(), in_ray.direction());
    }
    else
    {
      scattered_dir = refract(rec.normal(), unit_vector(in_ray.direction()), eta_ratio);
    }
    scattered_ray = ray(rec.p(), scattered_dir);
    return true;
  }
};

#endif