#include "shape.hpp"
#include <iostream>

Shape::Shape(std::string const& name, Material const& material) :
	name_{name},
	material_{material} {  }

Shape::~Shape() {}
