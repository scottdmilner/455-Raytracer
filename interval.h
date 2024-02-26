//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_INTERVAL_H
#define RAY_TRACER_INTERVAL_H


#include "general.h"

class interval {
public:
    double min, max;
    interval() : min(+infinity), max(-infinity) {} // flip-flopped == empty
    interval(double min, double max) : min(min), max(max) {}

    [[nodiscard]] bool contains(double x) const {
        return (x >= min) && (x <= max);
    }

    [[nodiscard]] bool surrounds (double x) const {
        return (x > min) && (x < max);
    }

    static const interval empty, universe;
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);



#endif //RAY_TRACER_INTERVAL_H
