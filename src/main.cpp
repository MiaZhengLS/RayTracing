#include <iostream>
#include <fstream>
#include "common.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "color.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

int main()
{
  hittable_list world;
  shared_ptr<material> mat_ground = make_shared<lambertian>(color(0.8, 0.8, 0.8));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, mat_ground));
  const double r = 0.2;
  const double min_dist = 4 * pow(r, 2);
  std::vector<point3> all_centers;
  auto collide_with_others = [&](const point3 &new_center)
  {
    for (const point3 &previous_center : all_centers)
    {
      if ((new_center - previous_center).length_squared() < min_dist)
      {
        return true;
      }
    }
    return false;
  };
  for (int i = -10; i < 10; ++i)
  {
    for (int j = -6; j < 6; ++j)
    {
      const point3 center = vec3(i, r, j) + vec3(random_double(-5, 5), 0, random_double(-5, 5));
      if (center.length_squared() >= 9 && !collide_with_others(center))
      {
        all_centers.push_back(center);

        const double rd_mat = random_double(0, 1);
        shared_ptr<material> mat;
        if (rd_mat < 0.4)
        {
          mat = make_shared<lambertian>(color::random());
        }
        else if (rd_mat < 0.6)
        {
          mat = make_shared<dielectric>(random_double(1, 2));
        }
        else
        {
          mat = make_shared<metal>(color::random(), random_double(0, 1));
        }
        world.add(make_shared<sphere>(center, 0.2, mat));
      }
    }
  }
  std::cout << "valid sphere " << all_centers.size() << std::endl;
  const point3 in_focus_pos = point3(-0.4, 1, -2);
  shared_ptr<material> mat_glass = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(in_focus_pos, 1, mat_glass));
  world.add(make_shared<sphere>(in_focus_pos, -.8, mat_glass));
  shared_ptr<material> mat_metal = make_shared<metal>(color::random(0.3, 1), random_double(0, 1));
  world.add(make_shared<sphere>(point3(-1.5, 1, 0.3), 1, mat_metal));
  shared_ptr<material> mat_lambertian = make_shared<lambertian>(color::random());
  world.add(make_shared<sphere>(point3(2.5, 1, -.5), 1, mat_lambertian));

  const double aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const point3 look_from = point3(-4, 2.2, -10);
  const vec3 look_dir = -look_from;
  const vec3 camera_up = vec3(0, 1, 0);
  const int vfov = 30;
  const int sample_per_pixel = 20;
  const int max_recursion_depth = 20;
  const double focus_dist = (look_from - in_focus_pos).length();
  const double defocus_angle = 1.3;
  std::ofstream outFile("./output.ppm");
  camera main_camera(look_from, look_dir, camera_up, aspect_ratio, image_width, focus_dist, sample_per_pixel, max_recursion_depth, vfov, defocus_angle);
  main_camera.render_to_stream(world, outFile);
  outFile.close();
}
