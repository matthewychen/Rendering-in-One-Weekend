#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "interval.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable>> objects {}; //generates a dynamic sized array of pointers to hittable objects

    hittable_list() {} //empty initialization
    hittable_list(shared_ptr<hittable> object) { add(object); }//add any items initialized

    void clear() { objects.clear(); }//erase list. std::vector function

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);//append item with std::vector class function
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;
        

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }
};

#endif