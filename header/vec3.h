#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cstdlib>

using std::sqrt;
inline double random_double()
{
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
  return min + (max - min) * random_double();
}

class vec3
{
public:
  vec3() : e_{0.0, 0.0, 0.0} {}
  vec3(double e0, double e1, double e2) : e_{e0, e1, e2} {}
  ~vec3() {}

  double x() const { return e_[0]; }
  double y() const { return e_[1]; }
  double z() const { return e_[2]; }

  vec3 operator-() const { return vec3(-e_[0], -e_[1], -e_[2]); }
  double operator[](int index) const { return e_[index]; }
  double &operator[](int index) { return e_[index]; }
  vec3 &operator+=(const vec3 &v)
  {
    e_[0] += v.e_[0];
    e_[1] += v.e_[1];
    e_[2] += v.e_[2];
    return *this;
  }

  vec3 &operator*=(const double t)
  {
    e_[0] *= t;
    e_[1] *= t;
    e_[2] *= t;
    return *this;
  }

  vec3 &operator/=(const double t)
  {
    return *this *= 1 / t;
  }

  double length_squared() const
  {
    return e_[0] * e_[0] + e_[1] * e_[1] + e_[2] * e_[2];
  }

  double length() const
  {
    return sqrt(length_squared());
  }

  bool near_zero() const
  {
    double n = 1e-8;
    return fabs(e_[0]) < n && fabs(e_[1]) < n && fabs(e_[2]) < n;
  }

  static vec3 random()
  {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max)
  {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }

private:
  double e_[3];
};

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
  return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
  return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
  return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(const vec3 &v, const double t)
{
  return vec3(t * v[0], t * v[1], t * v[2]);
}

inline vec3 operator*(const double t, const vec3 &v)
{
  return v * t;
}

inline vec3 operator/(const vec3 &v, const double t)
{
  return v * (1 / t);
}

inline double dot(const vec3 &u, const vec3 &v)
{
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
  return vec3(u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vector(const vec3 &v)
{
  return v / v.length();
}

inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
  return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 random_unit_vector()
{
  return unit_vector(vec3::random(-1, 1));
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
  vec3 p = random_unit_vector();
  if (dot(p, normal) > 0.0)
  {
    return p;
  }
  else
  {
    return -p;
  }
}

inline vec3 random_on_disk()
{
  return random_double(-1, 1) * unit_vector(vec3(random_double(-1, 1), random_double(-1, 1), 0));
}

inline vec3 reflect(const vec3 &normal, const vec3 &in_dir)
{
  return in_dir - 2 * dot(normal, in_dir) * normal;
}

inline vec3 refract(const vec3 &normal, const vec3 &in_dir, const double eta_ratio)
{
  double cos_theta = fmin(dot(normal, -in_dir), 1.0);
  vec3 refract_perpendicular = eta_ratio * (in_dir + cos_theta * normal);
  vec3 refract_parallel = -sqrt(abs(1 - refract_perpendicular.length_squared())) * normal;
  return refract_perpendicular + refract_parallel;
}

#endif
