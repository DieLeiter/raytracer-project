#include "sdfwriter.hpp"
#include <iostream> // to debug with prints
#include <fstream> // opern, read, write, close files
#include <sstream> // stringstream for easier parsing
#include <string> // to buffer lines of the SDF File

void SdfWriter::write(float progress_percentage, std::string const& filename) const
{
    std::fstream myfile;
    myfile.open(filename, std::ios::out);

    //write materials
    myfile << "#materials" << std::endl
        << "define material red 0.7 0 0 0.1 0 0 0.1 0 0 100" << std::endl
        << "define material blue 0 0 0.7 0 0 0.1 0 0 0.1 100" << std::endl
        << "define material green 0 0.7 0 0 0.1 0 0 0.1 0 100" << std::endl
        << "define material yellow 0.7 0.7 0 0.1 0.1 0 0.1 0.1 0 100" << std::endl
        << "define material dark_white 0.1 0.1 0.1 0.1 0.1 0.1 0.4 0.4 0.4 550" << std::endl
        << "define material shiny_black 0.01 0.01 0.01 0 0 0 0.1 0.1 0.1 810" << std::endl
        << "define material white 0.7 0.7 0.7 0.2 0.2 0.2 0.2 0.2 0.2 810" << std::endl;

    //camera
    myfile << "#camera" << std::endl << "define camera eye 120.0 0 0 0 0 0 -1 0 1 0" << std::endl;

    //write geometry
    myfile << "#geometry" << std::endl
        << "define shape box floor -800 -200 2200 2200 -185 -800 dark_white" << std::endl
        << "define shape box left_floor -805 -200 2200 -800 2000 -800 dark_white" << std::endl
        << "define shape box back_floor -800 -200 -800 2200 2000 -805 dark_white" << std::endl
        << "define shape box red_cube -400 -185 -100 -100 115 -400 red" << std::endl
        << "define shape box green_cube -400 -185 100 -200 15 -100 green" << std::endl
        << "define shape box blue_cube -200 -185 -25 -125 -110 -100 blue" << std::endl
        << "define shape box yellow_cube -125 -185 -75 -100 -160 -100 yellow" << std::endl
        << "define shape box rotating_cube -50 -50 50 50 50 -50 shiny_black" << std::endl
        << "define shape sphere white_sphere 50 -155 50 30 white" << std::endl;

    //camera xform
    float cam_rotation_endvalue = 90.0f;

    myfile << "#camera xform" << std::endl
        << "transform eye translate 0 " << std::to_string(50 - 100 * progress_percentage) << " 400" << std::endl
        << "transform eye rotate " << std::to_string(cam_rotation_endvalue * progress_percentage) << " 0 1 0" << std::endl;

    //scene xform
    float box_rotation = 90.0f;
    float sphere_translation = 200.0f;

    if (progress_percentage <= 0.5f) {
        myfile << "#scene xform" << std::endl
            << "transform white_sphere translate 100 " << std::to_string(sphere_translation * progress_percentage) << " 0" << std::endl;
    }
    else {
        myfile << "#scene xform" << std::endl
            << "transform white_sphere translate 100 " << std::to_string(sphere_translation * (1.0f - progress_percentage)) << " 0" << std::endl;
    }
    /*myfile << "#scene xform" << std::endl
        << "transform rotating_cube rotate " << std::to_string(box_rotation * progress_percentage) << " 0 1 0" << std::endl
        << "transform rotating_cube translate -300 65 0" << std::endl;*/

    //lights: name, position, color, intensity
    myfile << "#lights" << std::endl 
        << "define light left_light -200 2000 1000 0.5 0.5 0.5 3" << std::endl
        << "ambient 0.1 0.1 0.1" << std::endl;

    //render
    myfile << "# ... and go" << std::endl << "render eye image.ppm 800 600" << std::endl;
}
