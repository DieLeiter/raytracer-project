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
    unsigned const image_width = 800;
    unsigned const image_height = 600;
    std::string const filename = "./checkerboard.ppm";
    Renderer renderer{image_width, image_height, filename};
    renderer.render();

    SdfParser sdf_parser{};
    Scenegraph scene{};
    
    if(argc < 2){ // 1st argument is filename
        std::cout << "You did non provide a SDF File!" << std::endl;
        return -1;
    }

    // pasring SDF File
    sdf_parser.parse(argv, scene);




    Window window{{image_width, image_height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         window.close();
        }
        window.show(renderer.color_buffer());
    }

  return 0;
}

void trace(Scenegraph& scene, Renderer &renderer, unsigned image_width, unsigned image_height) {

    float distance = (image_width / 2) / std::tan(scene.camera->fov_x / 2);

    for (unsigned i = image_height/2; i > -image_height/2; --i) {
        for (unsigned e = -image_width/2; e < image_width/2; ++e) {
            Ray ray{ glm::vec3(0, 0, 0), glm::vec3(e, i, distance) };

            for each(std::shared_ptr<Shape> shape in scene.objects) {
                
            }
        }
    }
}
