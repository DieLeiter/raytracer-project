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
  Color trace(Scenegraph& scene, Ray& ray);
  Color shade(Scenegraph& scene, HitPoint& hit);
  Color tone_mapping(Color calculated_color);
  Color reflection(Scenegraph& scene, HitPoint& hit);
  void write(Pixel const& p);

  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_ ;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

Ray transformRay(Ray const& ray, glm::mat4 const& matrix);

#endif // #ifndef BUW_RENDERER_HPP
