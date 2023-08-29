#include "bvh.h"

bvh::bvh(const std::vector<shared_ptr<hittable>> &objects, const size_t start, const size_t end)
{
  int object_count = end - start;
  std::vector<shared_ptr<hittable>> mutable_objects = objects;
  int compare_axis = random_int(0, 2);
  auto comparator = compare_axis == 0 ? aabb_cp_x : (compare_axis == 1 ? aabb_cp_y : aabb_cp_z);
  if (object_count == 1)
  {
    left = right = mutable_objects[start];
  }
  else if (object_count == 2)
  {
    if (comparator(mutable_objects[start], mutable_objects[start + 1]))
    {
      left = mutable_objects[start];
      right = mutable_objects[start + 1];
    }
    else
    {
      left = mutable_objects[start + 1];
      right = mutable_objects[start];
    }
  }
  else
  {
    std::sort(mutable_objects.begin() + start, mutable_objects.begin() + end, comparator);
    size_t middle = start + object_count / 2;
    left = make_shared<bvh>(mutable_objects, start, middle);
    right = make_shared<bvh>(mutable_objects, middle, end);
  }
  bounding_box_ = aabb(left->bounding_box(), right->bounding_box());
}

bool bvh::hit(const ray &r, const interval &ray_interval, hit_record &rec) const
{
  if (!bounding_box_.hit(r, ray_interval))
  {
    return false;
  }
  bool hit_left = left->hit(r, ray_interval, rec);
  bool hit_right = right->hit(r, interval(ray_interval.min(), hit_left ? rec.t() : ray_interval.max()), rec);
  return hit_left || hit_right;
}
