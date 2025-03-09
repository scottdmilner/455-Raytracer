//
// Created by Scott Milner on 2/21/24.
//

#ifndef RAY_TRACER_VEC3_H
#define RAY_TRACER_VEC3_H


#include <cmath>
#include <ostream>

class vec3;
inline vec3 norm(vec3);
inline double dot(const vec3 &v1, const vec3 &v2);

class vec3 {
public:
    // data
    double e[3];

    // constructors
    vec3() : e {0, 0, 0} {};
    vec3(double e0, double e1, double e2) : e {e0, e1, e2} {};

    // getters
    double x() { return e[0]; }
    double y() { return e[1]; }
    double z() { return e[2]; }

    // operators
    vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
    double operator[](int i) const { return e[i]; }
    double operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &other) {
        e[0] += other[0];
        e[1] += other[1];
        e[2] += other[2];
        return *this;
    }

    vec3& operator-=(const vec3 &other) {
        e[0] -= other[0];
        e[1] -= other[1];
        e[2] -= other[2];
        return *this;
    }

    vec3& operator*=(double &scalar) {
        e[0] *= scalar;
        e[1] *= scalar;
        e[2] *= scalar;
        return *this;
    }

    vec3& operator/=(double &scalar) {
        e[0] /= scalar;
        e[1] /= scalar;
        e[2] /= scalar;
        return *this;
    }

    [[nodiscard]] double len() const {
        return std::sqrt(len2());
    }

    [[nodiscard]] double len2() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static vec3 random() {
        return {random_double(), random_double(), random_double()};
    }
    static vec3 random(double min, double max) {
        return {random_double(min, max), random_double(min, max), random_double(min, max)};
    }
    static inline vec3 random_in_unit_sphere() {
        while (true) {
            auto p = vec3::random(-1,1);
            if (p.len2() < 1) {
                return p;
            }
        }
    }

    static inline vec3 random_in_unit_disk() {
        while (true) {
            auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
            if (p.len2() < 1) {
                return p;
            }
        }
    }

    static inline vec3 random_unit_vector() {
        return norm(random_in_unit_sphere());
    }

    static inline vec3 random_on_hemisphere(const vec3& normal) {
        vec3 on_unit_sphere = random_unit_vector();
        if (dot(on_unit_sphere, normal) > 0.0)
            return on_unit_sphere;
        else
            return -on_unit_sphere;
    }

};

// alias vec3 to point3
using point3 = vec3;

// more vec3 util functions

inline std::ostream& operator<<(std::ostream &str, const vec3& vec) {
    return str << vec.e[0] << ' ' << vec.e[1] << ' ' << vec.e[2];
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]};
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]};
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return {v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]};
}

inline vec3 operator*(const vec3 &v, const double s) {
    return {v.e[0] * s, v.e[1] * s, v.e[2] * s};
}

inline vec3 operator*(const double s, const vec3 &v) {
    return v * s;
}

inline vec3 operator/(const vec3 &v, const double s) {
    return {v.e[0] / s, v.e[1] / s, v.e[2] / s};
}

inline vec3 operator/(const double s, const vec3 &v) {
    return {s / v.e[0], s / v.e[1],s / v.e[2]};
}

inline vec3& operator/=(vec3 &v, const double s) {
    v.e[0] /= s;
    v.e[1] /= s;
    v.e[2] /= s;
    return v;
}

inline double dot(const vec3 &v1, const vec3 &v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return {
        v1[1]*v2[2] - v1[2]*v2[1],
        v2[0]*v1[2]-v1[0]*v2[2],
        v1[0]*v2[1]-v2[0]*v1[1]
    };
}

inline vec3 norm(const vec3 v) {
    return v / v.len();
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.len2())) * n;
    return r_out_perp + r_out_parallel;
}


#endif //RAY_TRACER_VEC3_H
