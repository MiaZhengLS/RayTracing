#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "color.h"
#include "hittable.h"

class camera
{
private:
  point3 center_;
  double aspect_ratio_;
  int img_width_;
  int img_height_;
  double focal_length_;
  double viewport_width_;
  double viewport_height_;
  vec3 pixel_delta_u_;
  vec3 pixel_delta_v_;
  point3 viewport_upper_left_;
  point3 pixel00_loc_;
  int sample_per_pixel_ = 10;

  color ray_color(ray r, const hittable &world) const;
  ray get_ray(int i, int j) const;
  vec3 pixel_sample_square() const;

public:
  camera(point3 center, double aspect_ratio, int img_width, double focal_length, double viewport_height);
  void render(const hittable &world) const;
};

#endif
