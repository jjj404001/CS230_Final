#include "Camera.h"
#define WHEEL_MEASURE 120
#define ROTATION_FACTOR 3.14159265f *2.0f / 20.0f
void Camera::SetSize(long input_right, long input_bottom)
{
	right_.x = input_right;
	up_.y    = input_bottom;
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

void Camera::RotateCamera()
{
	rotation_ += +ROTATION_FACTOR;
}