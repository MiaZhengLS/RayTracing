#ifndef MATERIAL_H
#define MATERIAL_H

#include "common.h"
#include "hittable.h"
#include "color.h"

class material
{
public:
  virtual ~material() = default;
  virtual bool scatter(const ray &in_ray, const hit_record &rec, color &attenuation, ray &scattered_ray) const = 0;
};

#endif