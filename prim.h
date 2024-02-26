//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_PRIM_H
#define RAY_TRACER_PRIM_H

#include "vec3.h"
#include "ray.h"
#include "shader.h"

class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
    // material info
    shader shader;
};

class prim {
public:
    virtual ~prim() = default;
    virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;
};


#endif //RAY_TRACER_PRIM_H
