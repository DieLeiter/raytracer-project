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
        << "define material dark_white 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 0.1 50" << std::endl
        << "define material white 0.7 0.7 0.7 0.2 0.2 0.2 0.2 0.2 0.2 810" << std::endl;

    //camera
    myfile << "#camera" << std::endl << "define camera eye 120.0 0 0 0 0 0 -1 0 1 0" << std::endl;

    //write geometry
    myfile << "#geometry" << std::endl
        << "define shape box floor -800 -200 800 800 -185 -800 dark_white" << std::endl
        << "define shape box red_cube -25 -185 25 25 -135 -25 red" << std::endl
        << "define shape box green_cube -25 -135 25 25 -85 -25 green" << std::endl
        << "define shape box blue_cube -25 -85 25 25 -35 -25 blue" << std::endl
        << "define shape box yellow_cube -25 -35 25 25 15 -25 yellow" << std::endl
        << "define shape sphere white_sphere 50 -155 -100 30 white" << std::endl;

    //camera xform
    float cam_rotation_endvalue = 90.0f;

    myfile << "#camera xform" << std::endl
        << "transform eye translate 0 0 300" << std::endl
        << "transform eye rotate " << std::to_string(cam_rotation_endvalue * progress_percentage) << " 0 1 0" << std::endl;

    //scene xform
    float red_rotation = 90.0f;
    float green_rotation = 180.0f;
    float blue_rotation = 270.0f;
    float yellow_rotation = 360.0f;
    float sphere_translation = 200.0f;
    float sphere_rotation = 360.0f;

    if (progress_percentage <= 0.5f) {
        myfile << "#scene xform" << std::endl
            << "transform white_sphere translate 100 " << std::to_string(sphere_translation * progress_percentage) << " 0" << std::endl;
    }
    else {
        myfile << "#scene xform" << std::endl
            << "transform white_sphere translate 100 " << std::to_string(sphere_translation * (1.0f - progress_percentage)) << " 0" << std::endl;
    }
    myfile << "#scene xform" << std::endl
        << "transform red_cube rotate " << std::to_string(red_rotation * progress_percentage) << " 0 1 0" << std::endl
        << "transform green_cube rotate " << std::to_string(green_rotation * progress_percentage) << " 0 1 0" << std::endl
        << "transform blue_cube rotate " << std::to_string(blue_rotation * progress_percentage) << " 0 1 0" << std::endl
        << "transform yellow_cube rotate " << std::to_string(yellow_rotation * progress_percentage) << " 0 1 0" << std::endl;

    //lights: name, position, color, intensity
    myfile << "#lights" << std::endl 
        << "define light left_light -200 500 700 0.5 0.5 0.5 3" << std::endl
        << "ambient 0.1 0.1 0.1" << std::endl;

    //render
    myfile << "# ... and go" << std::endl << "render eye image.ppm 800 600" << std::endl;
}
