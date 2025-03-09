//
// Created by Scott Milner on 2/22/24.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <algorithm>
#include <iostream>
#include <random>
#include "general.h"
#include "prim.h"
#include "color.h"
#include "world.h"

class camera {
public:
    double aspect_ratio;
    int image_width;
    double focal_length;
    int samples;

    double defocus_angle = 45;
    double focus_dist = 0.005;

    camera(double ar, int iw, double fl, int s) : aspect_ratio(ar), image_width(iw), image_height(0), focal_length(fl), samples(s) {}

    void render(const world& world, dual_stream& out) {
        initialize();

        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                color pixel_color = color{0,0,0};
                for (int s = 0; s < samples; ++s) {
                    auto pixel_center = pixel00_loc
                            + (i * pixel_delta_u) + pixel_delta_u * ((1.0f * rand() / RAND_MAX) - 0.5)
                            + (j * pixel_delta_v) + pixel_delta_v * ((1.0f * rand() / RAND_MAX) - 0.5);
                    auto ray_direction = norm(pixel_center - camera_center);
                    ray r((defocus_angle <= 0) ? camera_center : defocus_disk_sample(), ray_direction);
                    hit_record rec;
                    rec.ray_depth = 0;
                    pixel_color += ray_color(r, world, rec);
                }
                pixel_color /= (samples / 1.0);
                write_color(out, pixel_color);
            }
        }
        std::clog << "\rDone             \n";
    }
private:
    int image_height;
    point3 camera_center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    vec3 defocus_disk_u;
    vec3 defocus_disk_v;


    void initialize() {
        srand(5);
        rand();
        image_height = static_cast<int>(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1: image_height;

        camera_center = point3(0, 0, 0);

        // Viewport
//        auto focal_length = 1.0;
        auto viewport_height = 0.5;
        auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

        // Viewport vectors
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_ul = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_ul + pixel_delta_u / 2 + pixel_delta_v / 2;
        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2))*1000;
        defocus_disk_u = pixel_delta_u * defocus_radius;
        defocus_disk_v = pixel_delta_v *  defocus_radius;
    }

    point3 defocus_disk_sample() const {
        // random point in defocus disk
        auto p = vec3::random_in_unit_disk();
        return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    [[nodiscard]] color ray_color(const ray& r, const world& world, hit_record rec) const {
        int MAX_RAY_DEPTH = 3;
        double epsilon = 0.00001;

        if (world.scene.hit(r, {epsilon, infinity}, rec)) {
            double light_intensity = 1.3;
            color light_color = {1.0, 1.0, 1.0};
            vec3 light_dir = norm({1.0, 1.0, 1.0});

            color ambient_color = {0.1, 0.1, 0.1};
            color ambient = rec.shader.ambient_coefficient * ambient_color * rec.shader.diffuse_color;

            //ray shadow_ray{rec.p + epsilon * rec.normal, light_dir};
            //hit_record shadow_rec;
            color col;
            if (false) {
            // if (world.scene.hit(shadow_ray, {0, infinity}, shadow_rec)) {
                col = ambient;
            }
            else {
                // diffuse
//                color diffuse = rec.shader.diffuse_coefficient * light_intensity * light_color * rec.shader.diffuse_color * std::max(0.0, dot(rec.normal, light_dir));
                if (MAX_RAY_DEPTH <= rec.ray_depth) {
                    col = {0,0,0 };
                } else {
                    vec3 direction = rec.normal + vec3::random_on_hemisphere(rec.normal);
                    hit_record diffuse_rec;
                    diffuse_rec.ray_depth = rec.ray_depth + 1;
                    color diffuse =
                            rec.shader.diffuse_coefficient * light_intensity * light_color * rec.shader.diffuse_color *
                            std::max(0.0, dot(rec.normal, light_dir)) *
                            ray_color({rec.p, direction}, world, diffuse_rec);
                    // add randomized unit vector for lambertian diffuse
                    vec3 view_dir = norm(
                            norm(-r.dir()) + norm({1.0f * std::rand(), 1.0f * std::rand(), 1.0f * std::rand()}));
                    vec3 reflection_dir = 2 * rec.normal * dot(light_dir, rec.normal) - light_dir;

//                color spec = rec.shader.specular_coefficient * light_intensity * light_color * rec.shader.specular_color * std::pow(std::max(0.0, dot(view_dir, reflection_dir)), rec.shader.gloss_factor);

                    col = ambient + diffuse; // + spec;
                }
            }

            double reflectance = 1;
            // transmission
            if ((rec.shader.transmission > 0.0)) {
                if (MAX_RAY_DEPTH <=  rec.ray_depth) {
                    col = {0,0,0};
                }
                else {
                    bool front_facing = dot(rec.normal, r.dir()) < 0.0;
                    double ior = 1.5;
                    double ri = front_facing ? (1.0 / ior) : ior;
                    vec3 unit_dir = norm(r.dir());

//                    // sch = r0 + (1-r0)*pow(1 - fmin(dot(unit_dir, rec.normal), 1.0), 5);


                    vec3 refracted = refract(unit_dir, rec.normal, ri);

                    hit_record transmission_rec;
                    transmission_rec.ray_depth = rec.ray_depth + 1;
                    color refraction_col = rec.shader.transmission_color * ray_color({rec.p + epsilon * refracted, refracted}, world, transmission_rec);
                    col = (col * (1 - rec.shader.transmission)) + (refraction_col * rec.shader.transmission);
                }
            }

            // glossy
            if ((rec.shader.reflection > 0.0) && (MAX_RAY_DEPTH > rec.ray_depth)) {
                    reflectance *= rec.shader.reflection;

                    vec3 reflection_dir = ((1 - rec.shader.roughness) * (r.dir() - 2 * dot(r.dir(), rec.normal) * rec.normal)) + (rec.shader.roughness * vec3::random_on_hemisphere(rec.normal));

                    ray reflection_ray{rec.p + epsilon * reflection_dir, reflection_dir};
                    hit_record reflection_rec;
                    reflection_rec.ray_depth = rec.ray_depth + 1;
                    color reflection_col = rec.shader.specular_color * ray_color(reflection_ray, world, reflection_rec);
                    col = (col * (1 - reflectance)) + (reflection_col * reflectance);
            }



            col.e[0] = std::min(1.0, col.e[0]);
            col.e[1] = std::min(1.0, col.e[1]);
            col.e[2] = std::min(1.0, col.e[2]);
            return col;
        }

        // else sky
        vec3 unit_direction = norm(r.dir());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1, 1, 1) + a*color(0.5, 0.7, 1);
        return {0.2, 0.2, 0.2};
    }

};


#endif //RAY_TRACER_CAMERA_H
