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

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color{0.0, 0.0, 0.0})
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
        p.color = Color{0.0f, 1.0f, float(x)/height_};
      } else {
        p.color = Color{1.0f, 0.0f, float(y)/width_};
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::render(Scenegraph& scene)
{
    for (int y = 0; y < (int)height_; ++y) {
        for (int x = 0; x < (int)width_; ++x) {
            Ray ray = scene.camera->compute_eye_ray(width_, height_, x, y);

            Color pixel_color = trace(scene, ray);

            /*pixel_color.r = pixel_color.r / (pixel_color.r + 1);
            pixel_color.r = pixel_color.g / (pixel_color.g + 1);
            pixel_color.r = pixel_color.b / (pixel_color.b + 1);*/

            Pixel pixel{ (unsigned)x, (unsigned)y };
            pixel.color = pixel_color;

            write(pixel);
        }
    }
    ppm_.save(filename_);
}

Color Renderer::trace(Scenegraph& scene, Ray& ray)
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
        return Color{ 0.0f, 0.0f, 0.2f };
    }
    
    std::sort(hits.begin(), hits.end());

    return shade(scene, *hits.begin());
}

Color Renderer::shade(Scenegraph& scene, HitPoint& hit)
{
    // combute ambient light part
    float red = scene.ambient->r * hit.material.ka.r;
    float green = scene.ambient->g * hit.material.ka.g;
    float blue = scene.ambient->b * hit.material.ka.b;

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
    for (auto const& light : visible_lights) {
        glm::vec3 direction_light{ glm::normalize(light->position - hit.hit_point) }; // get direction to light
        glm::vec3 direction_reflection{ glm::normalize(glm::reflect(direction_light, glm::normalize(hit.normale))) };

        Color kd = hit.material.kd;
        Color ks = hit.material.ks;
        red += light->intensity * (kd.r * std::max(0.0f, glm::dot(direction_light, glm::normalize(hit.normale))) + ks.r * pow(std::max(0.0f, glm::dot(direction_reflection, hit.direction)), hit.material.m));
        green += light->intensity * (kd.g * std::max(0.0f, glm::dot(direction_light, glm::normalize(hit.normale))) + ks.g * pow(std::max(0.0f, glm::dot(direction_reflection, hit.direction)), hit.material.m));
        blue += light->intensity * (kd.b * std::max(0.0f, glm::dot(direction_light, glm::normalize(hit.normale))) + ks.b * pow(std::max(0.0f, glm::dot(direction_reflection, hit.direction)), hit.material.m));
    }

    return Color{ red, green, blue };
}

Ray Renderer::compute_eye_ray(Camera const& camera, int x, int y)
{
    //radians = degrees * pi / 180 ;
    /*float camera_angle_rad = camera.fov_x * M_PI / 180.0f;
    float distance = (width_ / 2) / std::tan(camera_angle_rad / 2); // compute plane distance

    float ray_x = (int)width_ / 2 - ((int)width_ - x);
    float ray_y = (int)height_ / 2 - ((int)height_ - y);
   
    return Ray{ glm::vec3(0, 0, 0), glm::normalize(glm::vec3(ray_x, ray_y, -distance)) };*/ // compute ray from camera through picture plane
    return Ray{};
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
