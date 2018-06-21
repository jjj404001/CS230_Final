#include "Camera.h"
#define WHEEL_MEASURE 120
#define TRANSLATION_FACTOR 10.0f
#define SCALE_FACTOR 1.0f
#define ROTATION_FACTOR 3.14159265f *2.0f / 20.0f

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

affine2d Camera::CameraToWorld() const
{
	const affine2d TranslationAndRotation = { right_.x,  right_.y, 0.0f,
										up_.x,     up_.y, 0.0f,
										center_.x, center_.y, 1.0f };

	return TranslationAndRotation;
}

affine2d Camera::WorldToCamera() const
{
	affine2d CameraToWorldMatrix = CameraToWorld();

	// Build camera to world matrix's inverse matrix.

	affine2d translationInverse = { 1.0f,      0.0f, 0.0f,
									0.0f,      1.0f, 0.0f,
									-CameraToWorldMatrix(2,0), -CameraToWorldMatrix(2,1), 1.0f };



	affine2d rotationInverse = { CameraToWorldMatrix(0,0), CameraToWorldMatrix(0,1), 0.0f,
								CameraToWorldMatrix(1,0), CameraToWorldMatrix(1,1), 0.0f,
								0.0f, 0.0f, 1.0f };


	return rotationInverse * translationInverse;
}


