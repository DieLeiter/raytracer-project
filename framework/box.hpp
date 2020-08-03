#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
public:
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(std::string name, Color const& color, glm::vec3 const& min, glm::vec3 const& max);
	~Box();
	float area() const override;
	float volume() const override;
	std::ostream& print(std::ostream& os) const override;

protected:
	glm::vec3 min_;
	glm::vec3 max_;
};

std::ostream& operator<<(std::ostream& os, Box const& b);

#endif