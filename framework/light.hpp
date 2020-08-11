#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
	std::string name_ = " ";
	glm::vec3 position_{ 0, 0 ,0 };
	Color color_{ 1.0f, 1.0f, 1.0f };
	float intensity_ = 10.0f;
};

#endif
