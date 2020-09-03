// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>

#include "scenegraph.hpp"
#include "ray.hpp"

class Renderer
{
public:
  //Renderer() = default; 
  Renderer(unsigned w, unsigned h, std::string const& file);
  

  void render();
  void render(Scenegraph& scene, int counter);
  glm::vec3 trace(Scenegraph& scene, Ray& ray);
  glm::vec3 shade(Scenegraph& scene, HitPoint& hit);
  glm::vec3 tone_mapping(glm::vec3 calculated_color);
  glm::vec3 reflection(Scenegraph& scene, HitPoint& hit);
  void write(Pixel const& p);

  inline std::vector<glm::vec3> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_ ;
  unsigned height_;
  std::vector<glm::vec3> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

Ray transformRay(Ray const& ray, glm::mat4 const& matrix);

#endif // #ifndef BUW_RENDERER_HPP
