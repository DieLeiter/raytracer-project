#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <string>

struct Camera
{
	std::string name = "Camera";
	float fov_x = 45.0f;

	Camera(std::string const& n, float angle) :
		name{n},
		fov_x{angle} {}
};

#endif
