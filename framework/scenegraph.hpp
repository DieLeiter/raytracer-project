#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <vector>

struct Scenegraph
{
	Camera* camera = nullptr;
	std::vector<std::shared_ptr<Shape>> objects{};
	std::vector<std::shared_ptr<Light>> lights{};
};

#endif
