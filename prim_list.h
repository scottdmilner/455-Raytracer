//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_PRIM_LIST_H
#define RAY_TRACER_PRIM_LIST_H

#include <memory>
#include <vector>

#include "prim.h"
#include "shader.h"

using std::shared_ptr;
using std::make_shared;

class prim_list : public prim {
public:
    std::vector<shared_ptr<prim>> objects;

    prim_list() = default;
    prim_list(const shared_ptr<prim>& obj) { add(obj); }

    void clear() { objects.clear(); }
    void add(const shared_ptr<prim>& obj) {
        objects.push_back(obj);
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override{
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& obj : objects) {
            if (obj->hit(r, interval{ray_t.min, closest_so_far}, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};


#endif //RAY_TRACER_PRIM_LIST_H
