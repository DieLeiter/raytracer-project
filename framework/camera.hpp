#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "ray.hpp"

class Camera
{
public:
	Camera(std::string const& n, float angle, glm::vec3 const& position, glm::vec3 const& direction, glm::vec3 const& upvektor);
	glm::mat4 compute_transform();
	Ray compute_eye_ray(unsigned width, unsigned height, int x, int y) const;
private:
	std::string name_ = "Camera";
	float fov_x_ = 45.0f;
	glm::vec3 eye_ = {0.0f, 0.0f, 0.0f};
	glm::vec3 dir_ = {0.0f, 0.0f, 0.0f};
	glm::vec3 up_ = {0.0f, 0.0f, 0.0f};
	glm::mat4 transform_{};
};

#endif
