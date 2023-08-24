#include <iostream>
#include "common.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main()
{
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -20, -5), 20));

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  double focal_length = 1.0;
  double viewport_height = 2.0;
  point3 camera_center = point3(0, 0, 0);
  camera main_camera(camera_center, aspect_ratio, image_width, focal_length, viewport_height);
  main_camera.render(world);
}
