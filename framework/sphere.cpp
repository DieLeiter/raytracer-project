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

	glm::vec3 hitpoint = ray.origin + distance * ray.direction;
	glm::vec3 normale = intersectNormale(hitpoint);

	glm::vec4 hitpoint_transformed = world_transformation_ * glm::vec4(hitpoint, 1.0f);
	glm::vec4 normale_transformed = glm::transpose(world_transformation_inv_) * glm::vec4{ glm::normalize(normale), 0.0f };
	hitpoint = { hitpoint_transformed.x, hitpoint_transformed.y, hitpoint_transformed.z };
	normale = { normale_transformed.x, normale_transformed.y, normale_transformed.z };
	return HitPoint(hit, distance, name_, material_, hitpoint, ray.direction, glm::normalize(normale));
}

glm::vec3 Sphere::intersectNormale(glm::vec3 const& hit_point) const
{
	return glm::vec3{ hit_point - center_ };
}
