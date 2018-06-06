#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"

class Object
{
	friend class Graphics;

	Transform transform_;
	Mesh mesh_;
	Texture texture_;
public:
	unsigned int shader;

	void Update(RECT input_rect);
};