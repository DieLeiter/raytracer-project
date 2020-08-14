#ifndef TRACER_HPP
#define TRACER_HPP

#include "scenegraph.hpp"
#include "renderer.hpp"

class Tracer {
public:
	void trace(Scenegraph& scene, Renderer& renderer, unsigned image_width, unsigned image_height) const;
};

#endif