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
	/* TODO 
	world_transformation_ *= glm::rotate(world_transformation_, angle, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_);*/
}

void Shape::scale(glm::vec3 const& axis)
{
	/* TODO
	world_transformation_ = glm::scale(world_transformation_, axis);
	world_transformation_inv_ = glm::inverse(world_transformation_); */
}

void Shape::translate(glm::vec3 const& axis)
{
	glm::mat4 transform_matrix = glm::mat4{
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		glm::vec4(axis.x, axis.y, axis.z, 1.0f) };

	//world_transformation_ = glm::translate(world_transformation_, axis);
	world_transformation_ *= transform_matrix;
	std::cout << world_transformation_[0].x << " " << world_transformation_[1].x << " " << world_transformation_[2].x << " " << world_transformation_[3].x << " " << std::endl;
	std::cout << world_transformation_[0].y << " " << world_transformation_[1].y << " " << world_transformation_[2].y << " " << world_transformation_[3].y << " " << std::endl;
	std::cout << world_transformation_[0].z << " " << world_transformation_[1].z << " " << world_transformation_[2].z << " " << world_transformation_[3].z << " " << std::endl;
	std::cout << world_transformation_[0].w << " " << world_transformation_[1].w << " " << world_transformation_[2].w << " " << world_transformation_[3].w << " " << std::endl;
	world_transformation_inv_ = glm::inverse(world_transformation_);
}

Shape::~Shape() {}
