#ifndef MATERIAL_HPP
#define MATERIAL_HPP

//#include "color.hpp"
#include <glm/glm.hpp>

struct Material
{
	glm::vec3 ka = { 0.0f, 0.0f, 0.0f };
	glm::vec3 kd = { 0.0f, 0.0f, 0.0f };
	glm::vec3 ks = { 0.0f, 0.0f, 0.0f };
	float m = 10.0f;
};

#endif
