#define _USE_MATH_DEFINES

#include "sphere.hpp"
#include "renderer.hpp"
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

HitPoint Sphere::intersect(Ray const& r) const
{
	Ray ray = transformRay(r, world_transformation_inv_);
	float distance = 0;
	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, pow(radius_, 2), distance);
	glm::vec4 hitpoint_transformed = glm::transpose(world_transformation_) * glm::vec4(ray.origin + distance * ray.direction, 1.0f);
	glm::vec3 hitpoint{ hitpoint_transformed.x, hitpoint_transformed.y, hitpoint_transformed.z };
	glm::vec4 normale = glm::normalize(glm::transpose(world_transformation_inv_) * glm::vec4{ intersectNormale(hitpoint), 0.0f });
	return HitPoint(hit, distance, name_, material_, hitpoint, ray.direction, {normale.x, normale.y, normale.z});
}

glm::vec3 Sphere::intersectNormale(glm::vec3 const& hit_point) const
{
	return glm::vec3{ hit_point.x - center_.x, hit_point.y - center_.y, hit_point.z - center_.z };
}
