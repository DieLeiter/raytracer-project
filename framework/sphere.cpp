#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include <cmath>
#include <iostream>

Sphere::Sphere(glm::vec3 const& cntr, float r) :
	center_{ cntr },
	radius_{ r } { std::cout << "Sphere Constructor" << std::endl; }

Sphere::Sphere(std::string name, Color const& color, glm::vec3 const& cntr, float r) :
	Shape(name, color),
	center_{ cntr },
	radius_{ r } { std::cout << "Sphere Constructor" << std::endl; }

Sphere::~Sphere()
{
	std::cout << "Sphere Destructor" << std::endl;
}

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
	glm::vec3 direction = glm::normalize(ray.direction);
	float distance = 0;
	bool hit = glm::intersectRaySphere(ray.origin, direction, center_, pow(radius_, 2), distance);
	glm::vec3 hitpoint{ ray.origin.x + (distance * direction.x),
							ray.origin.y + (distance * direction.y), 
							ray.origin.z + (distance * direction.z) };

	return HitPoint(hit, distance, name_, color_, hitpoint, direction);
}

std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	os << ", Center (x|y|z): " << center_.x << " | " << center_.y << " | " << center_.z << ", Radius: " << radius_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Sphere const& s)
{
	return s.print(os);
}
