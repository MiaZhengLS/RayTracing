#include <fstream>

#include "camera.h"
#include "material.h"

camera::camera(point3 center, double aspect_ratio, int img_width, double focal_length, const int max_depth, double vfov) : center_(center), aspect_ratio_(aspect_ratio), img_width_(img_width), focal_length_(focal_length), max_depth_(max_depth), vfov_(vfov)
{
  int h = static_cast<int>(img_width_ / aspect_ratio_);
  img_height_ = h < 1 ? 1 : h;

  double radian = degree_to_radian(vfov_);
  viewport_height_ = tan(radian / 2) * focal_length_ * 2;
  viewport_width_ = viewport_height_ * static_cast<double>(img_width_) / img_height_;

  vec3 viewport_u = vec3(viewport_width_, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height_, 0);

  pixel_delta_u_ = viewport_u / img_width_;
  pixel_delta_v_ = viewport_v / img_height_;

  viewport_upper_left_ = center_ - vec3(0, 0, focal_length_) - viewport_u / 2 - viewport_v / 2;
  pixel00_loc_ = viewport_upper_left_ + pixel_delta_u_ / 2 + pixel_delta_v_ / 2;
}

void camera::render(const hittable &world) const
{
  std::ofstream outFile("./output.ppm");
  if (outFile.is_open())
  {
    outFile << "P3\n"
            << img_width_ << " " << img_height_ << "\n255\n";
    for (size_t j = 0; j < img_height_; j++)
    {
      // std::clog << "\rScanlines remaining:" << (image_height - j) << " " << std::flush;
      for (size_t i = 0; i < img_width_; i++)
      {
        color pixel_color;
        for (size_t sample = 0; sample < sample_per_pixel_; sample++)
        {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, max_depth_, world);
        }
        write_color(outFile, pixel_color, sample_per_pixel_);
      }
    }
  }
  std::clog << "\rDone.\n";
}

ray camera::get_ray(int i, int j) const
{
  vec3 pixel_center = pixel00_loc_ + i * pixel_delta_u_ + j * pixel_delta_v_;
  vec3 pixel_sample = pixel_center + pixel_sample_square();
  vec3 ray_origin = center_;
  vec3 ray_dir = pixel_sample - ray_origin;
  return ray(ray_origin, ray_dir);
}

// See https://www.researchgate.net/publication/244986797 for a better understanding of pixels
// Pixel is just a point, not a square
// We sample within the square(we define) with the pixel as the center
vec3 camera::pixel_sample_square() const
{
  double px = -0.5 + random_double();
  double py = -0.5 + random_double();
  return (px * pixel_delta_u_) + (py * pixel_delta_v_);
}

color camera::ray_color(ray r, const int max_depth, const hittable &world) const
{
  if (max_depth == 0)
  {
    return color(0, 0, 0);
  }
  hit_record rec;
  // Use 0.001 instead of 0 to avoid shadow acene(self shadowing)
  if (world.hit(r, interval(0.001, infinity), rec))
  {
    color attenuation;
    ray scattered_ray;
    if (rec.mat()->scatter(r, rec, attenuation, scattered_ray))
    {
      return attenuation * ray_color(scattered_ray, max_depth - 1, world);
    }
    return color(0, 0, 0);
  }

  vec3 r_unit_vector = unit_vector(r.direction());
  double a = 0.5 * (r_unit_vector.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
