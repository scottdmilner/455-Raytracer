//
// Created by Scott Milner on 3/9/24.
//

#ifndef RAY_TRACER_TRI_H
#define RAY_TRACER_TRI_H


#include "prim.h"
#include "interval.h"

class tri : public prim {
public:
    tri(point3 p1, point3 p2, point3 p3, bool double_sided, shader shader)
    : p1(p1), p2(p2), p3(p3), double_sided(double_sided), shader(shader) {
        v13 = p3 - p1; // p3 -> p1
        v21 = p1 - p2; // p1 -> p2
        v32 = p2 - p3; // p2 -> p3
        normal = norm(cross(v21, v32));
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
        double facing_factor = dot(r.dir(), normal);
        if ((not double_sided) && (facing_factor >= 0))
            return false; // facing away or parallel to plane

        double t = dot(p1 - r.origin(), normal) / facing_factor;
        if (t <= ray_t.min || t >= ray_t.max)
            return false; // intersection not in range

        point3 p = r.at(t);

        if ((dot(cross(p - p1, v21), normal) < 0)
         || (dot(cross(p - p3, v13), normal) < 0)
         || (dot(cross(p - p2, v32), normal) < 0))
            return false; // not in triangle

        rec.t = t;
        rec.p = p;
        rec.normal = normal;
        rec.shader = shader;

        return true;
    }
private:
    // assume counter-clockwise order
    point3 p1;
    point3 p2;
    point3 p3;
    vec3 normal;
    bool double_sided;
    shader shader;

    vec3 v21;
    vec3 v32;
    vec3 v13;
};


#endif //RAY_TRACER_TRI_H
