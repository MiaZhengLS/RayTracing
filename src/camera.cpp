#include "camera.h"
#include "material.h"

camera::camera(const point3 &look_from, const vec3 &look_dir, const vec3 &v_up, const double aspect_ratio, const int img_width, const double focus_dist, const int sample_per_pixel, const int max_depth, const double vfov, double defocus_angle) : look_from_(look_from), look_dir_(look_dir), v_up_(v_up), aspect_ratio_(aspect_ratio), img_width_(img_width), focus_dist_(focus_dist), sample_per_pixel_(sample_per_pixel), max_depth_(max_depth), vfov_(vfov), defocus_angle_(defocus_angle)
{
  int h = static_cast<int>(img_width_ / aspect_ratio_);
  img_height_ = h < 1 ? 1 : h;

  const vec3 w = -unit_vector(look_dir);
  const vec3 u = unit_vector(cross(v_up_, w));
  const vec3 v = cross(w, u);

  double radian = degree_to_radian(vfov_);
  double viewport_height = tan(radian / 2) * focus_dist_ * 2;
  viewport_width_ = viewport_height * static_cast<double>(img_width_) / img_height_;

  vec3 viewport_u = viewport_width_ * u;
  vec3 viewport_v = -viewport_height * v;

  pixel_delta_u_ = viewport_u / img_width_;
  pixel_delta_v_ = viewport_v / img_height_;

  viewport_upper_left_ = look_from_ - focus_dist_ * w - viewport_u / 2 - viewport_v / 2;
  pixel00_loc_ = viewport_upper_left_ + pixel_delta_u_ / 2 + pixel_delta_v_ / 2;

  const double defocus_radius = focus_dist_ * tan(degree_to_radian(defocus_angle_ / 2));
  defocus_u_ = u * defocus_radius;
  defocus_v_ = v * defocus_radius;
}

void camera::render_to_stream(const hittable &world, std::ostream &output_stream) const
{
  std::clog << "\rStart rendering...\n";
  output_stream << "P3\n"
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
      write_color(output_stream, pixel_color, sample_per_pixel_);
    }
  }
  std::clog << "\rDone.\n";
}

ray camera::get_ray(int i, int j) const
{
  vec3 pixel_center = pixel00_loc_ + i * pixel_delta_u_ + j * pixel_delta_v_;
  vec3 pixel_sample = pixel_center + pixel_sample_square();
  vec3 ray_origin = defocus_angle_ <= 0 ? look_from_ : defocus_get_ray();
  vec3 ray_dir = pixel_sample - ray_origin;
  return ray(ray_origin, ray_dir);
}

vec3 camera::defocus_get_ray() const
{
  const vec3 rd = random_on_disk();
  return look_from_ + defocus_u_ * rd[0] + defocus_v_ * rd[1];
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
