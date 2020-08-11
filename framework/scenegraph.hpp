#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "camera.hpp"
#include "shape.hpp"
#include <vector>

struct Scenegraph
{
	Camera* camera = nullptr;
	std::vector<Shape*> objects{};
};

#endif
