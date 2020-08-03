#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

class Shape {
public:
	Shape() = default;
	Shape(std::string name, Color const& color_);
	virtual ~Shape();
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual std::ostream& print(std::ostream& os) const;
protected:
	std::string name_ = "Shape";
	Color color_{ 128, 128, 128 };
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif