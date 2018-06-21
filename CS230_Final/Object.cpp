#include "Object.h"
#include "Camera.h"
#include <iostream>
#include "matrix4.h"
#define STANDARD 1000.0f
#define PI 3.14159265f 
// TODO : after check, implement with ndc.
void Object::Update(RECT input_rect, Camera input_camera)
{
	//// Loop through every vertecies.
	//{
	//	auto current_vertex = mesh_.vertices.begin();
	//	while (current_vertex != mesh_.vertices.end())
	//	{
	//		const auto x_comp = current_vertex;
	//		const auto y_comp = (current_vertex + 1);
	//		const auto z_comp = (current_vertex + 2);





	//		//// Using scale
	//		//*x_comp *= transform_.scale_.x;
	//		//*y_comp *= transform_.scale_.y;
	//		//const auto original_x = *x_comp;
	//		//// Using rotation
	//		//*x_comp = (original_x *  cosf(transform_.rotation_)) + (*y_comp * sinf(transform_.rotation_));
	//		//*y_comp = (original_x * -sinf(transform_.rotation_)) + (*y_comp * cosf(transform_.rotation_));
	//		//// Finally, using translation.
	//		//*x_comp += transform_.translation_.x + input_camera.GetCenter().x;
	//		//*y_comp += transform_.translation_.y + input_camera.GetCenter().y;


	//		// Move to next vertext position's x.
	//		current_vertex += Mesh::number_of_element_per_stride;
	//	}
	//}





	mesh_.Update_VAO_VBO();


	if (texture_.GetTextureData() != NULL)
		glBindTexture(GL_TEXTURE_2D, texture_.GetTextureData());
	glUseProgram(shader);

	const auto proj = affine2d::build_affine_scale(input_camera.zoom_ / input_rect.right, input_camera.zoom_ / input_rect.bottom);
	auto view = affine2d::build_affine_identity();
	auto world = affine2d::build_affine_identity();

	// rotation.
	view.affine_map[0][0] = input_camera.right_.x;
	view.affine_map[0][1] = input_camera.right_.y;
	view.affine_map[1][0] = input_camera.up_.x;
	view.affine_map[1][1] = input_camera.up_.y;
	// translation to opposite direction, to make it to 0.
	view.affine_map[0][2] = input_camera.right_ * input_camera.center_;
	view.affine_map[1][2] = input_camera.up_    * input_camera.center_;



	const auto T = affine2d::build_affine_translation(transform_.translation_.x, transform_.translation_.y);
	const auto R = affine2d::build_affine_rotation(-transform_.rotation_);
	const auto S = affine2d::build_affine_scale(transform_.scale_.x, transform_.scale_.y);


	world = S * R;// *T;



	const auto uniCombined = glGetUniformLocation(shader, "combined");
	const auto combined = proj * view * world;

	glUniformMatrix3fv(uniCombined, 1, GL_FALSE, &combined.affine_map[0][0]);
	// proj * view * world * point
	//glUniformMatrix4fv(worldoc, 1, )
	//auto combined = proj * view * world;
	// combined * point


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
