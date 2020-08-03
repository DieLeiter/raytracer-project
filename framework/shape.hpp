#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"
#include "material.hpp"

class Shape {
public:
	Shape() = default;
	Shape(std::string const& name, Material const& matrial);
	virtual ~Shape();
	virtual float area() const = 0;
	virtual float volume() const = 0;
protected:
	std::string name_ = "Shape";
	Color color_{ 128, 128, 128 };
	Material material_{};
};

#endif