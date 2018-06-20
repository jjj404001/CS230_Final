#include "Object.h"
#include "Camera.h"
#include <iostream>
#include "matrix4.h"
#define STANDARD 1000.0f
#define PI 3.14159265f 
// TODO : after check, implement with ndc.
void Object::Update(Camera input_rect)
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
	//		//*x_comp += transform_.translation_.x + input_rect.GetCenter().x;
	//		//*y_comp += transform_.translation_.y + input_rect.GetCenter().y;


	//		// Move to next vertext position's x.
	//		current_vertex += Mesh::number_of_element_per_stride;
	//	}
	//}





	mesh_.Update_VAO_VBO();


	if (texture_.GetTextureData() != NULL)
		glBindTexture(GL_TEXTURE_2D, texture_.GetTextureData());
	glUseProgram(shader);


	const auto uniCombined = glGetUniformLocation(shader, "combined");
	const auto uniTranslate = glGetUniformLocation(shader, "translate");


	matrix4 proj = matrix4::Build_scale(vector2(1 / (input_rect.right_.x * input_rect.zoom_ / 2), 1 / (input_rect.up_.y * input_rect.zoom_ / 2)))
				 * matrix4::Build_rotation(input_rect.rotation_);
	matrix4 view_t = matrix4::Build_identity();
	matrix4 view_r = matrix4::Build_identity();
	matrix4 view   = matrix4::Build_identity();
	matrix4 world;



	view_t.value[0][3] = -input_rect.center_.x;
	view_t.value[1][3] = -input_rect.center_.y;

	view_r.value[0][0] = input_rect.right_.x / 2;//ux
	view_r.value[0][1] = input_rect.right_.y / 2;//uy
	view_r.value[1][0] = input_rect.up_.x / 2;//vx
	view_r.value[1][1] = input_rect.up_.y / 2;//vy



	view = view_r * view_t;

	const auto S = vector2(transform_.scale_.x / (input_rect.right_.x * input_rect.zoom_ / 2), transform_.scale_.y / (input_rect.up_.y * input_rect.zoom_ / 2));
	const auto R = transform_.rotation_ + input_rect.rotation_;
	const auto T = vector3(-transform_.translation_.x / (input_rect.right_.x * input_rect.zoom_), -transform_.translation_.y / (input_rect.up_.y * input_rect.zoom_), 0.0f);


	world = matrix4::Build_scale(S) * matrix4::Build_rotation(R) *matrix4::Build_translation(T);




	const auto combined = proj * view * world;

	glUniformMatrix4fv(uniCombined, 1, GL_FALSE, &combined.value[0][0]);
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
