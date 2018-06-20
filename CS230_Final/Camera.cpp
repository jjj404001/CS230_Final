#include "Camera.h"
#define WHEEL_MEASURE 120
#define TRANSLATION_FACTOR 10.0f
#define SCALE_FACTOR 1.0f
#define ROTATION_FACTOR 3.14159265f *2.0f / 20.0f
void Camera::SetSize(long input_right, long input_bottom)
{
	right_.x = static_cast<float>(input_right);
	up_.y    = static_cast<float>(input_bottom);
}

void Camera::ResizeCamera(short mouse_delta)
{
	mouse_delta /= WHEEL_MEASURE;
	mouse_delta = -mouse_delta;

	const auto multiply_factor = 1.0f - mouse_delta / 10.0f;

	//right_ *= zoom_;
	//up_    *= zoom_;

	zoom_ /= multiply_factor;
}
void Camera::MoveCamera(vector2 input_vector)
{
	center_ += input_vector;
}

void Camera::RotateCamera(vector2 input_vector)
{
	if(input_vector.x > 0)
		rotation_ += ROTATION_FACTOR;
	else
		rotation_ -= ROTATION_FACTOR;
}


