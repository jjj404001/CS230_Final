#include "Camera.h"

void Camera::SetSize(long input_right, long input_bottom)
{
	right_.x = input_right;
	up_.y    = input_bottom;
}