#include <renderer.hpp>
#include <window.hpp>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

#include "sdfparser.hpp"
#include "scenegraph.hpp"
#include "ray.hpp"
#include "shape.hpp"
#include "sdfwriter.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
    int framerate = 10;
    SdfParser sdf_parser{};
    Scenegraph scene{};
    SdfWriter sdf_writer{};
    Renderer renderer{0,0,"x"};
    std::string filename(argv[1]);
    for(int i = 0; i < framerate ; ++i){
        sdf_writer.write(i/framerate, filename);
        // pasring SDF File
        sdf_parser.parse(argv, scene);
        renderer = { scene.width, scene.height, scene.filename };
        //raytrace
        renderer.render(scene, i);
    }

    Window window{{scene.width, scene.height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         window.close();
        }
        window.show(renderer.color_buffer());
    }

    return 0;
}
