#include "box.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	min_{ min },
	max_{ max } { std::cout << "Box Constructor" << std::endl; }

Box::Box(std::string const& name, Material const& material, glm::vec3 const& min, glm::vec3 const& max) :
	Shape(name, material),
	min_{min},
	max_{max} { }

Box::~Box() { }

float Box::area() const
{
	float a = (max_.x - min_.x) * (max_.y - min_.y);
	float b = (max_.x - min_.x) * (max_.z - min_.z);
	float c = (max_.y - min_.y) * (max_.z - min_.z);

	return 2*a + 2*b + 2*c;
}

float Box::volume() const
{
	return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
}

HitPoint Box::intersect(Ray const& ray) const
{
	glm::vec3 direction = glm::normalize(ray.direction);
	std::vector<HitPoint> hits{};

	// front
	// check that ray is not parallel to x plane
	if (direction.x != 0) {
		float t = (-ray.origin.x + min_.x) / direction.x;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (y > min_.y && y < max_.y && z > min_.z && z < max_.z) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}


	// back
	// check that ray is not parallel to x plane
	if (direction.x != 0) {
		float t = (-ray.origin.x + max_.x) / direction.x;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (y > min_.y && y < max_.y && z > min_.z && z < max_.z) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}

	// left
	// check that ray is not parallel to x plane
	if (direction.z != 0) {
		float t = (-ray.origin.z + min_.z) / direction.z;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (y > min_.y && y < max_.y && x > min_.x && x < max_.x) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}

	// right
	// check that ray is not parallel to x plane
	if (direction.z != 0) {
		float t = (-ray.origin.z + max_.z) / direction.z;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (y > min_.y && y < max_.y && x > min_.x && x < max_.x) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}

	// bottom
	// check that ray is not parallel to x plane
	if (direction.y != 0) {
		float t = (-ray.origin.y + min_.y) / direction.y;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (x > min_.x && x < max_.x && z > min_.z && z < max_.z) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}

	// top
	// check that ray is not parallel to x plane
	if (direction.y != 0) {
		float t = (-ray.origin.y + max_.y) / direction.y;
		float x = ray.origin.x + t * direction.x;
		float y = ray.origin.y + t * direction.y;
		float z = ray.origin.z + t * direction.z;

		if (x > min_.x && x < max_.x && z > min_.z && z < max_.z) {
			float distance = sqrt(pow(ray.origin.x - x, 2) + pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
			HitPoint hit{ true, distance, name_, material_, glm::vec3(x, y, z), direction };
			hits.push_back(hit);
		}
	}

	if (hits.empty()) {
		return HitPoint();
	}
	else {
		std::sort(hits.begin(), hits.end());
		return *hits.begin();
	}
}
