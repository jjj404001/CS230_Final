#include "Object.h"
#include "Camera.h"
#include <iostream>
#include "matrix4.h"
#define STANDARD 1000.0f
#define PI 3.14159265f 
// TODO : after check, implement with ndc.
void Object::Update(RECT input_rect, Camera input_camera)
{
	mesh_.Update_VAO_VBO();


	if (texture_.GetTextureData() != NULL)
		glBindTexture(GL_TEXTURE_2D, texture_.GetTextureData());
	glUseProgram(shader);

	const auto proj = affine2d::build_affine_scale(input_camera.zoom_ * 2 / input_rect.right, input_camera.zoom_ * 2 / input_rect.bottom);
	auto view = affine2d::build_affine_identity();
	auto world = affine2d::build_affine_identity();

	

	
	// rotation.
	view.affine_map[0][0] = input_camera.right_.x;
	view.affine_map[0][1] = input_camera.right_.y;
	view.affine_map[1][0] = input_camera.up_.x;
	view.affine_map[1][1] = input_camera.up_.y;
	// translation to opposite direction, to make it to 0.
	view.affine_map[0][2] = input_camera.right_ * -input_camera.center_;
	view.affine_map[1][2] = input_camera.up_    * -input_camera.center_;

	view *= affine2d::build_affine_rotation(input_camera.rotation_);


	

	auto T = affine2d::build_affine_translation(transform_.translation_.x, transform_.translation_.y);
	auto R = affine2d::build_affine_rotation(-transform_.rotation_);
	auto S = affine2d::build_affine_scale(transform_.scale_.x, transform_.scale_.y);

	// WIP
	if (is_HUD)
	{
		T = affine2d::build_affine_translation(transform_.translation_.x - input_camera.center_.x, input_camera.center_.y);
		R *= affine2d::build_affine_rotation(-transform_.rotation_ -input_camera.rotation_);
		S *= affine2d::build_affine_scale(1/input_camera.zoom_); // 1 / zoom to convert to original scale.
	}
	// Use this order because we transpose.
	world =  T *  R * S ;

	



	const auto uniCombined = glGetUniformLocation(shader, "combined");
	const auto combined = (proj * view * world);

	glUniformMatrix3fv(uniCombined, 1, GL_TRUE, &combined.affine_map[0][0]);


	glBindVertexArray(mesh_.Get_VAO());
	glDrawArrays(mesh_.Get_Primitive(), 0, mesh_.Get_Num_of_vert());
}

Object::Object()
{
}

Object::Object(Transform input_transform, Mesh input_mesh)
{
	transform_ = input_transform;
	mesh_ = input_mesh;
}

Object::Object(Transform input_transform, Mesh input_mesh, Texture input_texture)
{
	transform_ = input_transform;
	mesh_ = input_mesh;
	texture_ = input_texture;
}
