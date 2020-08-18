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
#include "tracer.hpp"

//now single threaded again
int main(int argc, char* argv[])
{
    unsigned const image_width = 400;
    unsigned const image_height = 300;
    std::string const filename = "./checkerboard.ppm";
    Renderer renderer{image_width, image_height, filename};

    SdfParser sdf_parser{};
    Scenegraph scene{};
    
    if(argc < 2){ // 1st argument is filename
        std::cout << "You did non provide a SDF File!" << std::endl;
        return -1;
    }

    // pasring SDF File
    sdf_parser.parse(argv, scene);

    std::cout << "Camera name: " << scene.camera->name << std::endl;
    std::cout << "Object count: " << scene.objects.size() << std::endl;

    //raytrace
    /*Tracer tracer{};
    tracer.trace(scene, renderer, image_width, image_height);*/
    renderer.render(scene);

    Window window{{image_width, image_height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         window.close();
        }
        window.show(renderer.color_buffer());
    }

    return 0;
}
