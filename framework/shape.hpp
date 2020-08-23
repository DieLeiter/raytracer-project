#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "color.hpp"
#include "material.hpp"
#include "hitpoint.hpp"
#include "ray.hpp"

class Shape {
public:
	Shape() = default;
	Shape(std::string const& name, Material const& matrial);
	std::string name() const;
	void rotate(float angle, glm::vec3 const& axis);
	void scale(glm::vec3 const& axis);
	void translate(glm::vec3 const& axis);
	virtual ~Shape();
	virtual float area() const = 0;
	virtual float volume() const = 0;
	virtual HitPoint intersect(Ray const& r) const = 0;
	virtual glm::vec3 intersectNormale(glm::vec3 const& hit_point) const = 0;
protected:
	std::string name_ = "Shape";
	Color color_{ 128, 128, 128 };
	Material material_{};
	glm::mat4x4 world_transformation_{};
	glm::mat4x4 world_transformation_inv_{};
};

#endif