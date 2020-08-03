#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

struct HitPoint
{
	bool hit = false;
	float distance = 0.0f;
	std::string name = "Name";
	Color color = { 128, 128, 128 };
	glm::vec3 hit_point = { 0, 0, 0 };
	glm::vec3 direction = { 0, 0, 0 };
	HitPoint() = default;
	HitPoint(bool h, float d, std::string n, Color c, glm::vec3 hp, glm::vec3 dir) : 
		hit{h},
		distance{d},
		name{n},
		color{c},
		hit_point{hp},
		direction{dir} {}
};

#endif