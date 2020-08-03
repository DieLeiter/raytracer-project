#include "box.hpp"
#include <iostream>

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
