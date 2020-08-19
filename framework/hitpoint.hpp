#ifndef HITPOINT_HPP
#define HITPOINT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"
#include "ray.hpp"

struct HitPoint
{
	bool hit = false;
	float distance = 0.0f;
	std::string name = "Name";
	Material material{};
	glm::vec3 hit_point = { 0, 0, 0 };
	glm::vec3 direction = { 0, 0, 0 };
	glm::vec3 normale{};
	HitPoint() = default;
	HitPoint(bool h, float d, std::string n, Material m, glm::vec3 hp, glm::vec3 dir, glm::vec3 norm) : 
		hit{h},
		distance{d},
		name{n},
		material{m},
		hit_point{hp},
		direction{dir},
		normale{ norm } {}

	bool operator < (HitPoint const& hp) const {
		return distance < hp.distance;
	}
};

#endif