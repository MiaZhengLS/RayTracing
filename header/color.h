#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
using color = vec3;
inline void write_color(std::ostream &out, color pixel_color, int sample_per_pixel)
{
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  double percent = 1.0 / sample_per_pixel;
  r *= percent;
  g *= percent;
  b *= percent;

  static const interval intensity(0.000, 0.999);
  out << static_cast<int>(256 * intensity.clamp(r)) << ' '
      << static_cast<int>(256 * intensity.clamp(g)) << ' '
      << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

#endif