#pragma once
#include "Mesh.h"
#include "Transform.h"

class Object
{
	friend class Graphics;

	Transform transform_;


	Mesh mesh_;
public:
	void Update(RECT input_rect);
};