//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H


#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& dir) : o(origin), d(dir) {}
    point3 at(double t) const {
        return o + t*d;
    }
    [[nodiscard]] point3 origin() const { return o; }
    [[nodiscard]] vec3 dir() const { return d;}
private:
    point3 o;
    vec3 d;

};


#endif //RAY_TRACER_RAY_H
