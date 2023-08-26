#include <iostream>
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
  shared_ptr<material> mat_middle = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  shared_ptr<material> mat_left = make_shared<dielectric>(1.5);
  shared_ptr<material> mat_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.9);

  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, mat_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.3, mat_middle));
  world.add(make_shared<sphere>(point3(-.8, 0.0, -1.0), 0.5, mat_left));
  world.add(make_shared<sphere>(point3(.8, 0.0, -1.0), 0.5, mat_right));

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  double focal_length = 1.0;
  double viewport_height = 2.0;
  point3 camera_center = point3(0, 0, 0);
  camera main_camera(camera_center, aspect_ratio, image_width, focal_length, viewport_height, 50);
  main_camera.render(world);
}
