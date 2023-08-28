#include "sphere.h"

bool sphere::hit(const ray &r, const interval &ray_interval, hit_record &rec) const
{
  if (!bounding_box_.hit(r, ray_interval))
  {
    return false;
  }

  // To hit the sphere, there must be at least one point on the ray that is also on the sphere
  // From len(r-center)=r we can get (r-center)*(r-center)=r*r
  // r=A+tB, A is the origin of the ray, B is the direction of the ray, t is variable
  // (A+tB-center)*(A+tB-center)=r*r
  // (tB+(A-center))*(tB+(A-center))=r*r
  // dot(B,B)*t*t+2*dot(B,A-center)*t+dot(A-center,A-center)=r*r
  // This is a quadratic formula of t
  // To solve quadratic, we use (-b±√(b²-4ac))/(2a)
  // But here we just want to know if the ray hits the sphere or not
  // So we just check if √(b²-4ac) can stand
  vec3 dir = r.origin() - center_;
  double a = r.direction().length_squared();
  double b_half = dot(r.direction(), dir);
  double c = dir.length_squared() - radius_ * radius_;
  double discriminant = b_half * b_half - a * c;
  if (discriminant < 0)
  {
    return false;
  }
  double sqrt_d = sqrt(discriminant);
  double result = (-b_half - sqrt_d) / a;
  // Try another result
  if (!ray_interval.surrounds(result))
  {
    result = (-b_half + sqrt_d) / a;
    if (!ray_interval.surrounds(result))
    {
      return false;
    }
  }
  vec3 p = r.at(result);
  rec.set_record(p, result, (p - center_) / radius_, r.direction(), mat_);

  return true;
}