#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere(glm::vec3 const& cntr, float r) :
	center_{ cntr },
	radius_{ r } { }

Sphere::Sphere(std::string const& name, Material const& material, glm::vec3 const& cntr, float r) :
	Shape(name, material),
	center_{ cntr },
	radius_{ r } { }

Sphere::~Sphere() {}

float Sphere::area() const
{
	if (radius_ < 0) {
		std::cout << "Radius darf nicht negativ sein!" << std::endl;
		return -1;
	}
	return M_PI * 4 * pow(radius_, 2.0f);
}

float Sphere::volume() const
{
	if (radius_ < 0) {
		std::cout << "Radius darf nicht negativ sein!" << std::endl;
		return -1;
	}
	return (4 * M_PI * pow(radius_, 3.0f))/3;
}

HitPoint Sphere::intersect(Ray const& ray) const
{
	float distance = 0;
	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, pow(radius_, 2), distance);
	glm::vec3 hitpoint = ray.origin + distance * ray.direction;
	return HitPoint(hit, distance, name_, material_, hitpoint, ray.direction);
}
