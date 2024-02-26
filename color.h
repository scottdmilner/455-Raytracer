//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include "vec3.h"
#include "dual_stream.h"

using color = vec3;

void write_color(std::ostream &out, color col) {
    // write to out tranformed to [0...255]
    out << static_cast<int>(255.999 * col.x()) << ' '
        << static_cast<int>(255.999 * col.y()) << ' '
        << static_cast<int>(255.999 * col.z()) << '\n';
}

void write_color(dual_stream &out, color col) {
    // write to out tranformed to [0...255]
    out << static_cast<int>(255.999 * col.x()) << ' '
        << static_cast<int>(255.999 * col.y()) << ' '
        << static_cast<int>(255.999 * col.z()) << '\n';
}


#endif //RAY_TRACER_COLOR_H
