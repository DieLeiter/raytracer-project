#include "shape.hpp"
#include <iostream>

Shape::Shape(std::string name, Color const& color) :
	name_{name},
	color_{color} { std::cout << "Shape Constructor" << std::endl; }

Shape::~Shape()
{
	std::cout << "Shape Destructor" << std::endl;
}

std::ostream& Shape::print(std::ostream& os) const
{
	os << "Name: " << name_ << ", Color (RGB): " << color_.r << " | " << color_.g << " | " << color_.b;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}
