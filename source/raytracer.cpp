#include <renderer.hpp>
#include <window.hpp>
#include <iostream> // to debug with prints
#include <fstream> // opern, read, write, close files
#include <sstream> // stringstream for easier parsing
#include <string> // to buffer lines of the SDF File

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>

//now single threaded again
int main(int argc, char* argv[])
{
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";

  //Renderer renderer{image_width, image_height, filename};

  //renderer.render();

  /* parsing SDF File */
  if(argc < 2){ // 1st argument is filename
      std::cout << "You did non provide a SDF File!" << std::endl;
      return -1;
  }

  std::string const in_file_path = argv[1]; //in_file_path is assigned provided SDFFile
  std::ifstream in_file(in_file_path, std::ios::in); // open file in read-only && ASCII mode
  std::string line_buffer; //currently parsed line
  int32_t line_count = 0; //line number
  std::string class_name; // here the class name of the currently parsed line will be stored
  std::string identifier; // here the identifier (e.g. "define") of the currently parsed line will be stored
  std::string shape_type; //if class_name is shape, need to check for derived classes

  while(std::getline(in_file, line_buffer)){
    ++line_count;
    std::istringstream in_sstream(line_buffer); //default split token is whitespace

    /* TODO: check if line is empty, otherwise wrong parsing*/

    in_sstream >> identifier; //identifier is assigned the first word (until whitespace)

    if(identifier == "define"){
      in_sstream >> class_name; //class_name is assigned the next word in current line (until next whitespace)
      if(class_name == "shape"){
        //check what specific shape
        in_sstream >> shape_type;
        if(shape_type == "box"){
          std::string box_name;
          float min_x;
          float min_y;
          float min_z;
          float max_x;
          float max_y;
          float max_z;
          //TODO: lookup Material ??

          in_sstream >> box_name;
          in_sstream >> min_x >> min_y >> min_z;
          in_sstream >> max_x >> max_y >> max_z;
          //TODO: material

          std::cout << "Shape Box in line " << line_count << ": " << box_name << " " << min_x  << " " << min_y << " " << min_z  << " " << max_x  << " " << max_y << " " << max_z << " " << std::endl; // for testing only
          
        }
        else if(shape_type == "sphere"){
          std::string sphere_name;
          float center_x;
          float center_y; 
          float center_z;
          float radius;
          //TODO: material lookup

          in_sstream >> sphere_name;
          in_sstream >> center_x >> center_y >> center_z;
          in_sstream >> radius;
          //TODO: material

          std::cout << "Shape Sphere in line " << line_count << ": " << sphere_name << " " << center_x  << " " << center_y << " " << center_z << " " << radius << std::endl; // for testing only
        
        }
        else if(shape_type == "composite"){
          //TODO!!
        }
        else{
          std::cout << "Invalid shape type in line " << line_count << std::endl;
        }
        //parse shape attributes

      }
      else if(class_name == "material"){
        //parse material attributes
        std::string material_name;
        float ka_red, ka_green, ka_blue;
        float kd_red, kd_green, kd_blue;
        float ks_red, ks_green, ks_blue;
        float m;
 
        in_sstream >> material_name;
        in_sstream >> ka_red >> ka_green >> ka_blue;
        in_sstream >> m;
 
        std::cout << "Material in line " << line_count << ": " << material_name << " " << ka_red  << " " << ka_green << " " << ka_blue << " " << m << std::endl; // for testing only
      }
      else if(class_name == "light"){
        //parse light attributes
        std::string light_name; 
        float position_x;
        float position_y;
        float position_z;
        float color_r;
        float color_g;
        float color_b;
	      float intensity;

        in_sstream >> light_name;
        in_sstream >> position_x;
        in_sstream >> position_y;
        in_sstream >> position_z;
        in_sstream >> color_r;
        in_sstream >> color_g;
        in_sstream >> color_b;
        in_sstream >> intensity;

        std::cout << "Light in line " << line_count << ": " << light_name  << " " << position_x << " " << position_y << " " << position_z << " " << color_r <<  " " << color_g << " " << color_b << " " << intensity << std::endl; // for testing only
      }
      else if(class_name == "camera"){
        //parse camera attributes
        std::string camera_name; 
        float angle;
        in_sstream >> camera_name;
        in_sstream >> angle;

        std::cout << "Camera in line " << line_count << ": " << camera_name << " " << angle << std::endl; // for testing only
      }
      else{
        std::cout<<"Invalid line in SDF File. Unknown class name.";
      }
    }
  }
/* end of parsing */


 /* Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }*/

  return 0;
}
