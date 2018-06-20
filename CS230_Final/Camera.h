#pragma once
#include "vector2.hpp"
#include "affine2d.hpp"


class Camera
{
	friend class Graphics;
	friend class Object;

	vector2 center_{ 0, 0 };
	vector2 up_{ 0, 1 };
	vector2 right_{ 1, 0 };

	float zNear =  1.0f;
	float zFar  = -1.0f;

	float rotation_ = 0.0f;
	float zoom_    = 1.0f;

	float fov_ = 0.0f; // radian
public:
	Camera() = default;
	Camera(vector2 camera_center, vector2 camera_up);

	vector2 GetCenter() const { return center_; }
	void SetCenter(vector2 camera_center) { center_ = camera_center; };
	void SetSize(long input_right, long input_bottom);
	void ResizeCamera(short mouse_delta);
	void MoveCamera(vector2 input_vector);
	void RotateCamera(vector2 input_vector);
	vector2 GetUp() const { return up_; }
	vector2 GetRight() const { return right_; }
	float GetZoom() const { return zoom_; }
	float GetRotation() const { return rotation_; }
	float GetNear() const { return zNear; }
	float GetFar() const { return zFar; }

	void ResetUp(vector2 camera_up = { 0, 1 });

	void MoveUp(float distance);
	void MoveRight(float distance);
	void Rotate(float angle_radians);

	affine2d CameraToWorld() const;
	affine2d WorldToCamera() const;
};