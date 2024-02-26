//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_SHADER_H
#define RAY_TRACER_SHADER_H


#include "color.h"

class shader {
public:
    double diffuse_coefficient;
    double specular_coefficient;
    double ambient_coefficient;
    color diffuse_color;
    color specular_color;
    double gloss_factor;

    shader() = default;
};


#endif //RAY_TRACER_SHADER_H
