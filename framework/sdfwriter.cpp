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
        << "define material blue 0 0 0.7 0 0 0.1 0 0 0.1 10" << std::endl
        << "define material white 1 1 1 0.1 0.1 0.1 0.1 0.1 0.1 50" << std::endl;

    //write geometry
    myfile << "#geometry" << std::endl
        << "define shape box rbottom -100 -50 50 100 50 -50 red" << std::endl
        << "define shape box floor -200 -105 -200 200 -85 -800 white" << std::endl
        << "define shape sphere bsphere 0 0 0 30 white" << std::endl;

    //camera
    myfile << "#camera" << std::endl << "define camera eye 120.0 0 0 0 0 0 -1 0 1 0" << std::endl;

    //scene xform
    float scale_endvalue = 1.5f;
    float rotation_endvalue = 45.0f;

    myfile << "#scene xform" << std::endl
        << "transform rbottom rotate " << std::to_string(rotation_endvalue * progress_percentage) << " 0 1 0" << std::endl
        << "transform rbottom translate 0 100 -500" << std::endl
        << "transform bsphere scale " << std::to_string(scale_endvalue * progress_percentage) << " " << std::to_string(scale_endvalue * progress_percentage) << " " << std::to_string(scale_endvalue * progress_percentage) << std::endl
        << "transform bsphere translate 0 -30 -300" << std::endl;

    //lights
    myfile << "#lights" << std::endl 
        << "define light sun 0 0 0 0.7 0.7 0.7 5" << std::endl
        << "ambient 0.5 0.5 0.5" << std::endl;

    //render
    myfile << "# ... and go" << std::endl << "render eye image.ppm 800 600" << std::endl;
}
