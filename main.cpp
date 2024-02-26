#include <iostream>
#include <fstream>
#include <random>
#include "dual_stream.h"
#include "general.h"
#include "parris.h"
#include "prim_list.h"
#include "sphere.h"
#include "camera.h"

#define OUTFILE "out.ppm"


int main() {
    // set up output
    std::ofstream ofile;
    ofile.open(OUTFILE, std::ofstream ::out | std::ofstream ::trunc);
    auto out = dual_stream(std::cout, ofile);

    // WORLD
    prim_list world;
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
                        16.0 + 8.0 * std::rand() / RAND_MAX
                    }));
        }
    }


    // RENDER
//    camera cam(16.0 / 9.0, 1280);
    camera cam(1, 960);
    cam.render(world, out);

    ofile.close();
    return 0;
}
