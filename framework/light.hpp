#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{
	std::string name = " ";
	glm::vec3 position{ 0, 0 ,0 };
	Color color{ 1.0f, 1.0f, 1.0f };
	float intensity = 10.0f;
};

#endif
