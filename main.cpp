#include <iostream>
#include <fstream>
#include <random>
#include "dual_stream.h"
#include "general.h"
#include "parris.h"
#include "prim_list.h"
#include "sphere.h"
#include "camera.h"
#include "tri.h"
#include "suzanne.h"

#define OUTFILE "out.ppm"


int main() {
    // set up output
    std::ofstream ofile;
    ofile.open(OUTFILE, std::ofstream ::out | std::ofstream ::trunc);
    auto out = dual_stream(std::cout, ofile);

    // WORLD
//    prim_list world = suzanne().monkey;
//    world.add(make_shared<sphere>(
//            point3{0, -500, -1},
//            499.65,
//            shader{
//                0,
//                0,
//                1.0,
//                {0,0,0},
//                {0,0,0},
//                1.0,
//                0.8
//            }));
    // Part 2 scene 2
    prim_list world;
    world.add(make_shared<sphere>( // white sphere
            point3{0.5, 0.0, -1.15},
            0.05,
            shader{
                0.8,
                0.1,
                0.3,
                {1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0
            }));
    world.add(make_shared<sphere>( // red sphere
            point3{0.3, 0.0, -1.1},
            0.08,
            shader{
            0.8,
            0.8,
            0.1,
            {1.0, 0.0, 0.0},
            {0.5, 1.0, 0.5},
            32.0,
            0.0
            }));
    world.add(make_shared<sphere>( // green sphere
            point3{-0.6, 0.0, -1.0},
            0.3,
            shader{
                0.7,
                0.5,
                0.1,
                {0.0, 1.0, 0.0},
                {0.5, 1.0, 0.5},
                64.0,
                0.0
            }));
    world.add(make_shared<sphere>( // reflective sphere
            point3{0.1, -0.55, -0.75},
            0.3,
            shader{
                0.0,
                0.1,
                0.1,
                {0.75, 0.75, 0.75},
                {1.0, 1.0, 1.0},
                10.0,
                0.9
            }));
    world.add(make_shared<tri>( // blue triangle
            point3{0.3, -0.3, -1.4},
            point3{0.0, 0.3, -1.1},
            point3{-0.3, -0.3, -0.8},
            true,
            shader{
                0.9,
                0.9,
                0.1,
                {0.0, 0.0, 1.0},
                {1.0, 1.0, 1.0},
                32.0,
                0.0
            }));
    world.add(make_shared<tri>( // yellow triangle
            point3{-0.2, 0.1, -0.9},
            point3{-0.2, -0.5, -0.8},
            point3{-0.2, 0.1, -1.3},
            true,
            shader{
                0.9,
                0.5,
                0.1,
                {1.0, 1.0, 0.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0
            }));

    // Part 2, scene 1
    /*
    world.add(make_shared<sphere>(
            point3{0.0, 0.3, -2.0},
            0.25,
            shader{
                0.0,
                0.1,
                0.1,
                {0.75, 0.75, 0.75},
                {1.0, 1.0, 1.0},
                10.0,
                0.9
            }));
    world.add(make_shared<tri>(
            point3{0.0,-0.7,-1.5},
            point3{1.0,0.4,-2.0},
            point3{0.0,-0.7, -2.5},
            shader{
                0.9,
                1.0,
                0.1,
                {0.0, 0.0, 1.0},
                {1.0, 1.0, 1.0},
                4.0,
                0.0
            }));
    world.add(make_shared<tri>(
            point3{0.0,-0.7,-1.5},
            point3{0.0,-0.7, -2.5},
            point3{-1.0,0.4,-2.0},
            shader{
                    0.9,
                    1.0,
                    0.1,
                    {1.0, 1.0, 0.0},
                    {1.0, 1.0, 1.0},
                    4.0,
                    0.0
            }));
    */
//    world.add(make_shared<sphere>(point3(0, 0, -1), 0.4, ));
//    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    /*// white
    world.add(make_shared<sphere>(
            point3{0.45, 0.0, -1.15},
            0.15,
            shader{
                0.8,
                0.1,
                0.3,
                {1.0, 1.0, 1.0},
                {1.0, 1.0, 1.0},
                4.0
            }));
    // red
    world.add(make_shared<sphere>(
            point3{0.0, 0.0, -1.1},
            0.2,
            shader{
                    0.6,
                    0.3,
                    0.1,
                    {1.0, 0.0, 0.0},
                    {1.0, 1.0, 1.0},
                    32.0
            }));
    // green
    world.add(make_shared<sphere>(
            point3{-0.6, 0.0, -1.0},
            0.3,
            shader{
                    0.7,
                    0.2,
                    0.1,
                    {0.0, 1.0, 0.0},
                    {0.5, 1.0, 0.5},
                    64.0
            }));
    // blue
    world.add(make_shared<sphere>(
            point3{0., -10000.5, -1.0},
            10000.0,
            shader{
                    0.9,
                    0.0,
                    0.1,
                    {0.0, 0.0, 1.0},
                    {1.0, 1.0, 1.0},
                    16.0
            }));
*/
    // Parris
    /*
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            world.add(make_shared<sphere>(
                    point3{j / 100.0 - 0.5, -i / 100.0 + 0.5, -1.1 + 0.17  * std::rand() / RAND_MAX},
                    0.007 + 0.0025  * std::rand() / RAND_MAX,
                    shader{
                        0.7,
                        0.2,
                        0.1,
                        {parris::egbert[i][j][0] / 256, parris::egbert[i][j][1] / 256, parris::egbert[i][j][2] / 256},
                        {1.0, 1.0, 1.0},
                        16.0 + 8.0 * std::rand() / RAND_MAX,
                        0.5 * std::rand() / RAND_MAX
                    }));
        }
    }
    */

    // RENDER
//    camera cam(16.0 / 9.0, 1280);
    camera cam(1, 400, 0.5, 24);
    cam.render(world, out);

    ofile.close();
    return 0;
}
