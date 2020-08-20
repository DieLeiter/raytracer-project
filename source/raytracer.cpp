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

//now single threaded again
int main(int argc, char* argv[])
{
    SdfParser sdf_parser{};
    Scenegraph scene{};
    
    if(argc < 2){ // 1st argument is filename
        std::cout << "You did non provide a SDF File!" << std::endl;
        return -1;
    }

    // pasring SDF File
    sdf_parser.parse(argv, scene);

    Renderer renderer{ scene.width, scene.height, scene.filename };

    //raytrace
    renderer.render(scene);

    Window window{{scene.width, scene.height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         window.close();
        }
        window.show(renderer.color_buffer());
    }

    return 0;
}
