#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include "camera.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <vector>

struct Scenegraph
{
	std::shared_ptr<Camera> camera = nullptr;
	std::shared_ptr<glm::vec3> ambient{};
	std::vector<std::shared_ptr<Shape>> objects{};
	std::vector<std::shared_ptr<Light>> lights{};
};

#endif
