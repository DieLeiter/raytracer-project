#include "box.hpp"
#include <iostream>

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	min_{ min },
	max_{ max } { std::cout << "Box Constructor" << std::endl; }

Box::Box(std::string name, Color const& color, glm::vec3 const& min, glm::vec3 const& max) :
	Shape(name, color),
	min_{min},
	max_{max} { std::cout << "Box Constructor" << std::endl; }

Box::~Box()
{
	std::cout << "Box Destructor" << std::endl;
}

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

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	os << ", Min (x|y|z): " << min_.x << " | " << min_.y << " | " << min_.z << ", Max (x|y|z): " << max_.x << " | " << max_.y << " | " << max_.z;
	return os;
}

std::ostream& operator<<(std::ostream& os, Box const& b)
{
	return b.print(os);
}
