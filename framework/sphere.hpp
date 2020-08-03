#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"

class Sphere : public Shape {
public:
	Sphere(glm::vec3 const& cntr, float r);
	Sphere(std::string name, Color const& color, glm::vec3 const& cntr, float r);
	~Sphere();
	float area() const override;
	float volume() const override;
	HitPoint intersect(Ray const& ray) const;
	std::ostream& print(std::ostream& os) const override;

private:
	glm::vec3 center_;
	float radius_;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif