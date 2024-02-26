//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H


#include "prim.h"

class sphere : public prim {
public:
    sphere(point3 center, double radius, shader shader) : center(center), radius(radius), shader(shader) {}
    bool hit(const ray &r, interval ray_t, hit_record &rec) const override {
        vec3 oc = r.origin() - center;
        auto a = r.dir().len2();
        auto hb = dot(oc, r.dir());
        auto c = oc.len2() - radius * radius;

        auto discriminant = hb*hb - a*c;
        if (discriminant < 0) return false;

        auto sqrtd = std::sqrt(discriminant);

        // find nearest root within acceptable range
        auto root = (-hb - sqrtd) / a;
        if (root <= ray_t.min || ray_t.max <= root) {
            root = (-hb + sqrtd) / a;
            if (root <= ray_t.min || ray_t.max <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(root);
        rec.normal = (rec.p - center) / radius;
        rec.shader = shader;

        return true;
    }
private:
    point3 center;
    double radius;
    shader shader;
};


#endif //RAY_TRACER_SPHERE_H
