#ifndef BVH_H
#define BVH_H

#include "hittable_list.h"

class bvh : public hittable
{
private:
  aabb bounding_box_;
  shared_ptr<hittable> left;
  shared_ptr<hittable> right;

  static bool aabb_cp_min(const shared_ptr<hittable> a, const shared_ptr<hittable> b, const int axis)
  {
    return a->bounding_box().axis(axis).min() < b->bounding_box().axis(axis).min();
  }

  static bool aabb_cp_x(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
  {
    return aabb_cp_min(a, b, 0);
  }

  static bool aabb_cp_y(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
  {
    return aabb_cp_min(a, b, 1);
  }

  static bool aabb_cp_z(const shared_ptr<hittable> a, const shared_ptr<hittable> b)
  {
    return aabb_cp_min(a, b, 2);
  }

public:
  bvh(const hittable_list &world) : bvh(world.objects(), 0, world.objects().size())
  {
  }
  bvh(const std::vector<shared_ptr<hittable>> &objects, const size_t start, const size_t end);
  bool hit(const ray &r, const interval &ray_interval, hit_record &rec) const override;
  aabb bounding_box() const override { return bounding_box_; }
};

#endif