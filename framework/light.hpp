#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "color.hpp"

struct light
{
	glm::vec3 position_{ 0, 0 ,0 };
	Color color_{ 1.0f, 1.0f, 1.0f };
	float intesnity_ = 10.0f;
};

#endif
