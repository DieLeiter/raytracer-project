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
    //get framerate for animation
    int framerate;
    std::cout << "Werter Herr, Werte Dame, bitte insertieren Sie eine Frameanzahl: " << std::endl;
    std::cin >> framerate;

    SdfParser sdf_parser{};
    SdfWriter sdf_writer{};
    Renderer renderer{0,0,"x"};
    std::string filename(argv[1]);
    //animation
    for(int i = 1; i <= framerate ; ++i){
        sdf_writer.write((float)i/(float)framerate, filename);
        // pasring SDF File
        Scenegraph scene{};
        sdf_parser.parse(argv, scene);
        renderer = { scene.width, scene.height, scene.filename };
        //raytrace
        renderer.render(scene, i);

        std::cout << "Picture " << i << " of " << framerate << std::endl;
    }

    /*Window window{{width, height}};

    while (!window.should_close()) {
        if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
         window.close();
        }
        window.show(renderer.color_buffer());
    }*/

    return 0;
}
