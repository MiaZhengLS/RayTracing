#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "color.h"
#include "hittable.h"

class camera
{
private:
  point3 look_from_;
  vec3 look_dir_;
  vec3 v_up_;
  double aspect_ratio_;
  int img_width_;
  int img_height_;
  double focus_dist_;
  double viewport_width_;
  vec3 pixel_delta_u_;
  vec3 pixel_delta_v_;
  point3 viewport_upper_left_;
  point3 pixel00_loc_;
  // The more samples per pixel, the less noise
  int sample_per_pixel_ = 10;
  int max_depth_;
  double vfov_;
  // defocus_angle is used to calculate the blur radius, the higher, the blurrier
  // defocus_u/v simply multiply blur radius with camera transform u/v
  double defocus_angle_;
  vec3 defocus_u_;
  vec3 defocus_v_;

  color ray_color(ray r, const int max_depth, const hittable &world) const;
  ray get_ray(int i, int j) const;
  vec3 pixel_sample_square() const;
  vec3 defocus_get_ray() const;

public:
  camera(const point3 &look_from, const vec3 &look_dir, const vec3 &v_up, const double aspect_ratio, const int img_width, const double focus_dist, const int sample_per_pixel, const int max_depth = 10, const double vfov = 45, double defocus_angle = 0);
  void render_to_stream(const hittable &world, std::ostream &output_stream) const;
};

#endif
