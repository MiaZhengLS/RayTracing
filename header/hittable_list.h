#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>

#include "hittable.h"

using std::shared_ptr;


class hittable_list:public hittable
{
private:
  std::vector<shared_ptr<hittable>> objects_;

public:
  hittable_list(){}
  hittable_list(shared_ptr<hittable> object) { add(object); }
  void clear() { objects_.clear(); }
  void add(shared_ptr<hittable> object) { objects_.push_back(object); }
  bool hit(const ray &r, const interval &ray_interval, hit_record &rec) const override;
};


#endif
