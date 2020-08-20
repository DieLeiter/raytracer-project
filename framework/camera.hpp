#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>

struct Camera
{
	std::string name = "Camera";
	float fov_x = 45.0f;
	glm::vec3 eye = {0.0f, 0.0f, 0.0f};
	glm::vec3 dir = {0.0f, 0.0f, 0.0f};
	glm::vec3 up = {0.0f, 0.0f, 0.0f};

	Camera(std::string const& n, float angle,glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& upvektor) :
		name{n},
		fov_x{angle},
		eye{position},
		dir{direction},
		up{upvektor} {}		
};

#endif
