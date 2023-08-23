#include <iostream>
#include <fstream>
#include "color.h"
#include "common.h"
#include "hittable_list.h"
#include "sphere.h"

color ray_color(ray r, hittable_list world)
{
  hit_record rec;
  if (world.hit(r, 0.1, 1000, rec))
  {
    return 0.5 * (rec.normal() + color(1, 1, 1));
  }

  vec3 r_unit_vector = unit_vector(r.direction());
  return r_unit_vector;
}

int main()
{
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  int image_height = static_cast<int>(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -20, -5), 20));

  // Camera
  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * static_cast<double>(image_width) / image_height;
  point3 camera_center = point3(0, 0, 0);

  //
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // How far does each pixel cover in both directions
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // left top corner of the viewport
  point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
  // position of the first pixel
  point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  std::ofstream outFile("./output.ppm");
  if (outFile.is_open())
  {
    outFile << "P3\n"
            << image_width << " " << image_height << "\n255\n";
    for (size_t j = 0; j < image_height; j++)
    {
      // std::clog << "\rScanlines remaining:" << (image_height - j) << " " << std::flush;
      for (size_t i = 0; i < image_width; i++)
      {
        point3 pixel_center = pixel00_loc + pixel_delta_u * i + pixel_delta_v * j;
        vec3 ray_direction = pixel_center - camera_center;
        ray r(camera_center, ray_direction);
        color pixel_color = ray_color(r, world);
        write_color(outFile, pixel_color);
      }
    }
  }

  std::clog << "\rDone.\n";
}
