#pragma once
#include "vector2.hpp"

class Transform
{
	friend class Object;
	friend class Graphics;

	vector2 translation_ = vector2(0.0f, 0.0f);
	float rotation_   = 0.0f;
	vector2 scale_    = 1.0f;

public:
	void SetTranslation(vector2 input) { translation_ = input; };
	void SetRotation(float input) { rotation_ = input; };
	void SetScale(vector2 input) { scale_ = input; };

	vector2 GetScale() { return scale_; };
	vector2 GetTranslation() { return translation_; };

};