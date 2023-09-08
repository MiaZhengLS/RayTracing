#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"
#include "ray.h"

class texture
{
public:
  ~texture() = default;
  color value(double u, double v, const point3 &p) const;
};

class solid_color : public texture
{
private:
  color color_;

public:
  solid_color(color c) : color_(c) {}
  solid_color(double r, double g, double b) : color_(color(r, g, b)) {}
  color value(double u, double v, const point3 &p) const override { return color_; }
};


#endif