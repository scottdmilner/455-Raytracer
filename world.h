//
// Created by Scott Milner on 4/12/24.
//

#ifndef RAY_TRACER_WORLD_H
#define RAY_TRACER_WORLD_H


#include "prim_list.h"
#include "light.h"

class world {
public:
    prim_list scene;
    std::vector<light> lights;

    world() = default;
};


#endif //RAY_TRACER_WORLD_H
