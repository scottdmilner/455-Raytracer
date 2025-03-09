//
// Created by Scott Milner on 4/12/24.
//

#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H


#include "color.h"

class light {
virtual color col() const = 0;
};


#endif //RAY_TRACER_LIGHT_H
