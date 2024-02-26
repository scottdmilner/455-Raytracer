cmake_minimum_required(VERSION 3.27)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracer main.cpp
        dual_stream.h
        vec3.h
        color.h
        ray.h
        prim.h
        sphere.h
        prim_list.h
        general.h
        interval.h
        camera.h
        shader.h
        parris.h)
