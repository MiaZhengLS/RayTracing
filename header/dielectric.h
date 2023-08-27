#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "vec3.h"

inline double reflectance(double cos_theta, double refraction_ratio)
{
  double r0 = (1 - refraction_ratio) / (1 + refraction_ratio);
  r0 *= r0;
  return r0 + (1 - r0) * pow((1 - cos_theta), 5);
}

class dielectric : public material
{
private:
  double refraction_index_;

public:
  dielectric(double refraction_index) : refraction_index_(refraction_index < 1 ? 1 : refraction_index) {}
  bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const override
  {
    attenuation = color(1, 1, 1);
    double refraction_ratio = rec.is_front_face() ? 1.0 / refraction_index_ : refraction_index_;
    double cos_theta = dot(unit_vector(in_ray.direction()), rec.normal());
    double sin_theta = sqrt(1 - cos_theta * cos_theta);
    vec3 scattered_dir;
    // Internal total reflection
    // https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf
    // sin(theta') = sin(theta) * refraction_ratio
    // Invalid sin value -> no refraction
    if (refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_double())
    {
      scattered_dir = reflect(rec.normal(), in_ray.direction());
    }
    else
    {
      scattered_dir = refract(rec.normal(), unit_vector(in_ray.direction()), refraction_ratio);
    }
    scattered_ray = ray(rec.p(), scattered_dir);
    return true;
  }
};

#endif