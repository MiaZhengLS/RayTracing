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

  shared_ptr<material> mat_ground = make_shared<lambertian>(color(0.6, 0.9, 0.6));
  shared_ptr<material> mat_middle = make_shared<lambertian>(color(0.7, 0.3, 0.3));
  shared_ptr<material> mat_left = make_shared<dielectric>(1.5) ;
  shared_ptr<material> mat_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.9);

  world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, mat_ground));
  world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, mat_middle));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, mat_left));
  world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, mat_left));
  world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, mat_right));

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  double focal_length = 1.0;
  point3 look_from = point3(-2, 1.6, 0.6);
  vec3 look_dir = vec3(2, -1, -2);
  vec3 camera_up = vec3(0, 1, 0);
  camera main_camera(look_from, look_dir, camera_up, aspect_ratio, image_width, focal_length, 50, 60);
  main_camera.render(world);
}
