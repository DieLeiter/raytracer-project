#include "sdfparser.hpp"
#include <iostream> // to debug with prints
#include <fstream> // opern, read, write, close files
#include <sstream> // stringstream for easier parsing
#include <string> // to buffer lines of the SDF File
#include <algorithm>

#include "box.hpp"
#include "sphere.hpp"

void SdfParser::parse(char* argv[], Scenegraph &scene) const
{
    std::string const in_file_path = argv[1]; //in_file_path is assigned provided SDFFile
    std::ifstream in_file(in_file_path, std::ios::in); // open file in read-only && ASCII mode
    std::string line_buffer; //currently parsed line
    int32_t line_count = 0; //line number
    std::string class_name; // here the class name of the currently parsed line will be stored
    std::string identifier; // here the identifier (e.g. "define") of the currently parsed line will be stored
    std::string shape_type; //if class_name is shape, need to check for derived classes

    while (std::getline(in_file, line_buffer)) {
        ++line_count;
        std::istringstream in_sstream(line_buffer); //default split token is whitespace

        /* TODO: check if line is empty, otherwise wrong parsing*/

        in_sstream >> identifier; //identifier is assigned the first word (until whitespace)

        if (identifier == "define") {
            in_sstream >> class_name; //class_name is assigned the next word in current line (until next whitespace)
            if (class_name == "shape") {
                //check what specific shape
                in_sstream >> shape_type;
                if (shape_type == "box") {
                    std::string box_name;
                    float min_x;
                    float min_y;
                    float min_z;
                    float max_x;
                    float max_y;
                    float max_z;
                    std::string box_material_name;

                    in_sstream >> box_name;
                    in_sstream >> min_x >> min_y >> min_z;
                    in_sstream >> max_x >> max_y >> max_z;
                    in_sstream >> box_material_name;

                    Material box_material{};
                    auto box_material_pair = scene.materials.find(box_material_name);
                    box_material = *box_material_pair->second; 

                    std::cout << "Shape Box in line " << line_count << ": " << box_name << " " << min_x << " " << min_y << " " << min_z << " " << max_x << " " << max_y << " " << max_z << " " << std::endl; // for testing only
                    auto box = std::make_shared<Box>(box_name, box_material, glm::vec3(min_x, min_y, min_z), glm::vec3(max_x, max_y, max_z));
                    scene.objects.push_back(box);
                }
                else if (shape_type == "sphere") {
                    std::string sphere_name;
                    float center_x;
                    float center_y;
                    float center_z;
                    float radius;
                    std::string sphere_material_name;

                    in_sstream >> sphere_name;
                    in_sstream >> center_x >> center_y >> center_z;
                    in_sstream >> radius;
                    in_sstream >> sphere_material_name;

                    Material sphere_material{};
                    auto sphere_material_pair = scene.materials.find(sphere_material_name);
                    sphere_material = *sphere_material_pair->second; 

                    std::cout << "Shape Sphere in line " << line_count << ": " << sphere_name << " " << center_x << " " << center_y << " " << center_z << " " << radius << std::endl; // for testing only
                    auto sphere = std::make_shared<Sphere>(sphere_name, sphere_material, glm::vec3(center_x, center_y, center_z), radius);

                    scene.objects.push_back(sphere);
                }
                else if (shape_type == "composite") {
                    //TODO!!
                }
                else {
                    std::cout << "Invalid shape type in line " << line_count << std::endl;
                }
                //parse shape attributes

            }
            else if (class_name == "material") {
                //parse material attributes
                std::string material_name;
                float ka_red, ka_green, ka_blue;
                float kd_red, kd_green, kd_blue;
                float ks_red, ks_green, ks_blue;
                float m;

                in_sstream >> material_name;
                in_sstream >> ka_red >> ka_green >> ka_blue;
                in_sstream >> kd_red >> kd_green >> kd_blue;
                in_sstream >> ks_red >> ks_green >> ks_blue;
                in_sstream >> m;

                Material joined = {{ka_red, ka_green, ka_blue}, {kd_red, kd_green, kd_blue}, {ks_red, ks_green, ks_blue}, m};
                auto material = std::make_shared<Material>(joined);
                scene.materials.insert(std::pair<std::string, std::shared_ptr<Material>>(material_name, material));
                std::cout << "Material in line " << line_count << ": " << material_name << " " << ka_red << " " << ka_green << " " << ka_blue << " " << m << std::endl; // for testing only
            }
            else if (class_name == "light") {
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

                Color light_color{ color_r, color_g, color_b };

                std::cout << "Light in line " << line_count << ": " << light_name << " " << position_x << " " << position_y << " " << position_z << " " << color_r << " " << color_g << " " << color_b << " " << intensity << std::endl; // for testing only
                std::shared_ptr<Light> light = std::make_shared<Light>(light_name, glm::vec3(position_x, position_y, position_z), light_color, intensity);

                scene.lights.push_back(light);
            }
            else if (class_name == "camera") {
                //parse camera attributes
                std::string camera_name;
                float angle;
                float position_x;
                float position_y;
                float position_z;
                float dir_x;
                float dir_y;
                float dir_z;
                float up_x;
                float up_y;
                float up_z;

                in_sstream >> camera_name;
                in_sstream >> angle;
                in_sstream >> position_x;
                in_sstream >> position_y;
                in_sstream >> position_z;
                in_sstream >> dir_x;
                in_sstream >> dir_y;
                in_sstream >> dir_z;
                in_sstream >> up_x;
                in_sstream >> up_y;
                in_sstream >> up_z;

                std::cout << "Camera in line " << line_count << ": " << camera_name << " " << angle << std::endl; // for testing only
                std::shared_ptr<Camera> camera = std::make_shared<Camera>(camera_name, angle, glm::vec3(position_x, position_y, position_z),glm::vec3(dir_x, dir_y, dir_z),glm::vec3(up_x, up_y, up_z));

                scene.camera = camera;
            }
            else {
                std::cout << "Invalid line in SDF File. Unknown class name.";
            }
        }
        else if (identifier == "ambient") {
            float ambient_r, ambient_g, ambient_b;

            in_sstream >> ambient_r >> ambient_g >> ambient_b;

            std::cout << "Light in line " << line_count << ": " << ambient_r << " " << ambient_g << " " << ambient_b << std::endl;
            std::shared_ptr<glm::vec3> ambient = std::make_shared<glm::vec3>(ambient_r, ambient_g, ambient_b);
            scene.ambient = ambient;
        }
        else if (identifier == "render") {
            unsigned height, width;
            std::string filename;
            std::string camera_name;

            in_sstream >> camera_name >> filename >> width >> height;

            std::cout << "Renderer in line " << line_count << ": " << camera_name << " " << filename << " " << width << " " << height << std::endl;
            scene.width = width;
            scene.height = height;
            scene.filename = filename;
        }
        else if (identifier == "transform") {
   
            std::string shape_name;
            std::string transform_type;

            in_sstream >> shape_name >> transform_type;

            if (transform_type == "rotate") {
                float angle, x_axis, y_axis, z_axis;
                in_sstream >> angle >> x_axis >> y_axis >> z_axis;

                std::cout << "Transformation in line " << line_count << ": " << shape_name << " " << transform_type << " " << angle << " " << x_axis << y_axis << z_axis << std::endl;

                auto find_by_name = [shape_name](std::shared_ptr<Shape> const& shape) -> bool {
                    return shape->name() == shape_name;
                };
                auto it = std::find_if(scene.objects.begin(), scene.objects.end(), find_by_name);
                
                if (it == scene.objects.end()) {
                    std::cout << "No object with this name!" << std::endl;
                }
                else {
                    (*(*it)).rotate(angle, { x_axis, y_axis, z_axis });
                }
            }
            else if (transform_type == "translate") {
                float x_axis, y_axis, z_axis;
                in_sstream >> x_axis >> y_axis >> z_axis;

                std::cout << "Transformation in line " << line_count << ": " << shape_name << " " << transform_type << " " << x_axis << y_axis << z_axis << std::endl;

                auto find_by_name = [shape_name](std::shared_ptr<Shape> const& shape) -> bool {
                    return shape->name() == shape_name;
                };
                auto it = std::find_if(scene.objects.begin(), scene.objects.end(), find_by_name);

                if (it == scene.objects.end()) {
                    std::cout << "No object with this name!" << std::endl;
                }
                else {
                    (*(*it)).translate({x_axis, y_axis, z_axis});
                }
            }
            else if (transform_type == "scale") {
                float x_axis, y_axis, z_axis;
                in_sstream >> x_axis >> y_axis >> z_axis;

                std::cout << "Transformation in line " << line_count << ": " << shape_name << " " << transform_type << " " << x_axis << y_axis << z_axis << std::endl;

                auto find_by_name = [shape_name](std::shared_ptr<Shape> const& shape) -> bool {
                    return shape->name() == shape_name;
                };
                auto it = std::find_if(scene.objects.begin(), scene.objects.end(), find_by_name);

                if (it == scene.objects.end()) {
                    std::cout << "No object with this name!" << std::endl;
                }
                else {
                    (*(*it)).scale({ x_axis, y_axis, z_axis });
                }
            }
        }
    }
}
