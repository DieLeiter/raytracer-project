// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#define _USE_MATH_DEFINES

#include "renderer.hpp"
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>


Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, glm::vec3{0.0, 0.0, 0.0})
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checker_pattern_size)%2) != ((y/checker_pattern_size)%2)) {
        p.color = glm::vec3{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = glm::vec3{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(Scenegraph& scene, int counter)
{
    for (int y = 0; y < (int)height_; ++y) {
        for (int x = 0; x < (int)width_; ++x) {
            Ray ray = scene.camera->compute_eye_ray(width_, height_, x, y);

            glm::vec3 pixel_color = trace(scene, ray);

            Pixel pixel{ (unsigned)x, (unsigned)y };
            pixel.color = pixel_color;

            write(pixel);
        }
    }
    ppm_.save(std::to_string(counter) + "_" + filename_);
}

glm::vec3 Renderer::trace(Scenegraph& scene, Ray& ray)
{
    std::vector<HitPoint> hits{};

    // try intersection for every scene object
    for (std::shared_ptr<Shape> shape : scene.objects) {
        HitPoint hit = shape->intersect(ray);

        if (hit.hit) {
            hits.push_back(hit);
        }
    }

    if (hits.empty()) {
        return glm::vec3{ 0.0f, 0.0f, 0.2f };
    }
    
    std::sort(hits.begin(), hits.end());

    return shade(scene, *hits.begin());
}

glm::vec3 Renderer::shade(Scenegraph& scene, HitPoint& hit)
{
    // compute ambient light
    glm::vec3 ambient = *scene.ambient * hit.material.ka;

    std::vector<std::shared_ptr<Light>>visible_lights{}; // lights that are visible from the hitpoint

    // check for visible lights
    for (std::shared_ptr<Light> const& light : scene.lights) {
        glm::vec3 direction_light{ glm::normalize(light->position - hit.hit_point) }; // get direction to light
        glm::vec3 origin = hit.hit_point + 0.1f * hit.normale; // ray origin with little offset, to avoid shadow acne
        Ray ray_light{ origin, direction_light };
        bool visible = true;

        for (std::shared_ptr<Shape> const& shape : scene.objects) {

            HitPoint shape_hit = shape->intersect(ray_light);

            if (shape_hit.hit) {
                visible = false;
                break;
            }
        }

        if (visible) {
            visible_lights.push_back(light);
        }
    }
    // compute color values with visible lights
    glm::vec3 calculated_color{0, 0, 0};

    for (auto const& light : visible_lights) {
        glm::vec3 direction_light{ glm::normalize(light->position - hit.hit_point) }; // get direction to light
        glm::vec3 direction_reflection{ glm::normalize(glm::reflect(direction_light, glm::normalize(hit.normale))) };

        glm::vec3 kd = hit.material.kd;
        glm::vec3 ks = hit.material.ks;
        //calculate diffus & specular
        glm::vec3 diffus = light->intensity * (kd * std::max(0.0f, glm::dot(direction_light, glm::normalize(hit.normale))));
        glm::vec3 specular = light->intensity * (ks * pow(std::max(0.0f, glm::dot(direction_reflection, hit.direction)), hit.material.m));

        //calculate color according to phong and add reflection
        glm::vec3 reflected_color = reflection(scene, hit);
        calculated_color = (ambient + diffus + specular) + ks * reflected_color;
    }
    return tone_mapping(calculated_color);
    //return calculated_color;
}

glm::vec3 Renderer::tone_mapping(glm::vec3 calculated_color){
  glm::vec3 max_value {0.7, 0.7, 0.7};
  glm::vec3 final_color = calculated_color / (max_value + calculated_color);
  return final_color;
}

glm::vec3 Renderer::reflection(Scenegraph& scene, HitPoint& hit){
              glm::vec3 reflected_direction = glm::reflect(glm::normalize(hit.direction),glm::normalize(hit.normale));
              Ray reflected_ray {hit.hit_point + 0.1f*hit.normale, glm::normalize(reflected_direction)};
              glm::vec3 reflected_color = trace(scene, reflected_ray);
              return reflected_color;   
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Ray transformRay(Ray const& ray, glm::mat4 const& matrix)
{
    glm::vec4 origin{ ray.origin, 1.0f };
    glm::vec4 direction{ ray.direction, 0.0f };

    origin = matrix * origin;
    direction = matrix * direction;
    return Ray{ {origin.x, origin.y, origin.z}, glm::normalize(glm::vec3(direction.x, direction.y, direction.z)) };
}
