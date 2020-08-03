#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
public:
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(std::string const& name, Material const& material, glm::vec3 const& min, glm::vec3 const& max);
	~Box();
	float area() const override;
	float volume() const override;

protected:
	glm::vec3 min_;
	glm::vec3 max_;
};

#endif