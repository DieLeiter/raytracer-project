#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"

struct Material
{
	Color ka = { 0.0f, 0.0f, 0.0f };
	Color kd = { 0.0f, 0.0f, 0.0f };
	Color ks = { 0.0f, 0.0f, 0.0f };
	float m = 10.0f;
};

#endif
