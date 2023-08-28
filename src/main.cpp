#include <iostream>
#include <set>
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
  const double r_square = r * r;
  std::set<point3> all_centers;
  auto collide_with_others = [&](const point3 &new_center)
  {
    for (const point3 &previous_center : all_centers)
    {
      if ((new_center - previous_center).length_squared() < r_square)
      {
        return true;
      }
    }
    return false;
  };
  int valid_spheres = 0;
  for (int i = -5; i < 5; ++i)
  {
    for (int j = -5; j < 5; ++j)
    {
      const point3 center = vec3(i, r, j) + vec3(random_double(-7, 7), 0, random_double(-7, 7));
      if (center.length_squared() > 4 && !collide_with_others(center))
      {
        valid_spheres++;
        all_centers.insert(center);
        const double rd_mat = random_double(0, 1);
        shared_ptr<material> mat;
        if (rd_mat < 0.3)
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
  std::cout << "valid sphere " << valid_spheres << std::endl;
  shared_ptr<material> mat_glass = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1, mat_glass));
  shared_ptr<material> mat_metal = make_shared<metal>(color::random(), random_double(0, 1));
  world.add(make_shared<sphere>(point3(2, 1, -1), 1, mat_metal));
  shared_ptr<material> mat_lambertian = make_shared<lambertian>(color::random());
  world.add(make_shared<sphere>(point3(-2, 1, 1), 1, mat_lambertian));

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 800;
  point3 look_from = point3(8, 2.0, 3);
  vec3 look_dir = -look_from;
  vec3 camera_up = vec3(0, 1, 0);
  double focus_dist = look_from.length();
  camera main_camera(look_from, look_dir, camera_up, aspect_ratio, image_width, focus_dist, 20, 30, 2);
  main_camera.render(world);
}
