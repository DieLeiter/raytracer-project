#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"

struct Material
{
	Color ka_ = { 0.0f, 0.0f, 0.0f };
	Color kd_ = { 0.0f, 0.0f, 0.0f };
	Color ks_ = { 0.0f, 0.0f, 0.0f };
	float m_ = 10.0f;
};

#endif
