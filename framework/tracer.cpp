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

                pixel.color = hit.material.ka;

                renderer.write(pixel);
            }
        }
    }
}
