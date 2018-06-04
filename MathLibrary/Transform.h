#pragma once
#include "vector2.hpp"

class Transform
{
	friend class Object;
	friend class Graphics;

	vector2 translation_ = vector2(0.0f, 0.0f);
	float rotation_ = 0.0f;
	float scale_    = 1.0f;
};