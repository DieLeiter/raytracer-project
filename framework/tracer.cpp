#define _USE_MATH_DEFINES

#include "tracer.hpp"
#include <algorithm>
#include <math.h>

void Tracer::trace(Scenegraph& scene, Renderer& renderer, unsigned image_width, unsigned image_height) const
{
    //radians = degrees * pi / 180 ;
    float camera_angle_rad = scene.camera->fov_x * M_PI / 180.0f;
    float distance = (image_width / 2) / std::tan(camera_angle_rad / 2);
    std::cout << "Computed Distance: " << distance << std::endl;

    for (int y = 0; y < (int)image_height; ++y) {

        for (int x = 0; x < (int)image_width; ++x) {
            //TODO: Ray Erzeugung in eigene Kamera Klasse auslagern
            float ray_x = (int)image_width / 2 - ((int)image_width - x);
            float ray_y = (int)image_height / 2 - ((int)image_height - y);
            Ray ray_viewer{ glm::vec3(0, 0, 0), glm::normalize(glm::vec3(ray_x, ray_y, -distance)) };
            

            std::vector<HitPoint> hits{};

            for (std::shared_ptr<Shape> shape : scene.objects) {

                HitPoint hit = shape->intersect(ray_viewer);

                if (hit.hit) {
                    hits.push_back(hit);
                }
            }

            Pixel pixel{ (unsigned)x, (unsigned)y };

            if (hits.empty()) {
                pixel.color = { 0.0, 0.0, 0.0 };

                renderer.write(pixel);
            }
            else {
                std::sort(hits.begin(), hits.end());

                HitPoint hit = *hits.begin();
                float red = scene.ambient->r * hit.material.ka.r;
                float green = scene.ambient->g * hit.material.ka.g;
                float blue = scene.ambient->b * hit.material.ka.b;

                
                std::vector<std::shared_ptr<Light>> visible_lights{}; // lights that are visible from the hitpoint
                
                // check for visible lights
                for (std::shared_ptr<Light> light : scene.lights) {
                    glm::vec3 direction_light{ light->position.x - hit.hit_point.x, light->position.y - hit.hit_point.y, light->position.z - hit.hit_point.z };
                    Ray ray_light{ hit.hit_point, glm::normalize(direction_light) };

                    for (std::shared_ptr<Shape> shape : scene.objects) {

                        HitPoint hit = shape->intersect(ray_light);

                        if (!hit.hit) {
                            visible_lights.push_back(light);
                        }
                    }
                }

                // compute color values with visible lights
                for (std::shared_ptr<Light> light : visible_lights) {
                    glm::vec3 direction_light{ light->position.x - hit.hit_point.x, light->position.y - hit.hit_point.y, light->position.z - hit.hit_point.z };
                    glm::vec3 direction_reflection = glm::reflect(direction_light, glm::normalize(hit.normale.direction));

                    Color kd = hit.material.kd;
                    Color ks = hit.material.ks;
                    red += light->intensity * (kd.r * glm::dot(glm::normalize(direction_light), glm::normalize(hit.normale.direction)) + ks.r * pow(glm::dot(glm::normalize(direction_reflection), glm::normalize(hit.direction)), hit.material.m));
                    green += light->intensity * (kd.g * glm::dot(glm::normalize(direction_light), glm::normalize(hit.normale.direction)) + ks.g * pow(glm::dot(glm::normalize(direction_reflection), glm::normalize(hit.direction)), hit.material.m));
                    blue += light->intensity * (kd.b * glm::dot(glm::normalize(direction_light), glm::normalize(hit.normale.direction)) + ks.b * pow(glm::dot(glm::normalize(direction_reflection), glm::normalize(hit.direction)), hit.material.m));
                }


                //pixel.color = hit.material.ka;
                pixel.color = { red, green, blue };

                renderer.write(pixel);
            }
        }
    }
}
