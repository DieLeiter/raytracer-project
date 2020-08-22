#include "shape.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Shape::Shape(std::string const& name, Material const& material) :
	name_{name},
	material_{ material } {}

std::string Shape::name() const
{
	return name_;
}

void Shape::rotate(float angle, glm::vec3 const& axis)
{
	world_transformation_ = glm::rotate(world_transformation_, angle, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::scale(glm::vec3 const& axis)
{
	world_transformation_ = glm::scale(world_transformation_, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::translate(glm::vec3 const& axis)
{
	world_transformation_ = glm::translate(world_transformation_, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);
}

Shape::~Shape() {}
