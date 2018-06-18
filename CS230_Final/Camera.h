#pragma once
#include "vector2.hpp"
#include "affine2d.hpp"


class Camera
{
	friend class Graphics;

	vector2 center_{ 0, 0 };
	vector2 up_{ 0, 1 };
	vector2 right_{ 1, 0 };
public:
	Camera() = default;
	Camera(vector2 camera_center, vector2 camera_up);

	vector2 GetCenter() const { return center_; };
	void SetCenter(vector2 camera_center);
	void SetSize(long input_right, long input_bottom);
	vector2 GetUp() const { return up_; };
	vector2 GetRight() const { return right_; };

	void ResetUp(vector2 camera_up = { 0, 1 });

	void MoveUp(float distance);
	void MoveRight(float distance);
	void Rotate(float angle_radians);

	affine2d CameraToWorld() const;
	affine2d WorldToCamera() const;
};