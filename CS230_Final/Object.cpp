#include "Object.h"
#include <iostream>


// TODO : after check, implement with ndc.
void Object::Update(RECT input_rect)
{
	// Loop through every vertecies.
	auto current_vertex = mesh_.vertices.begin();
	while (current_vertex != mesh_.vertices.end())
	{
		const auto x_comp = current_vertex;
		const auto y_comp = (current_vertex + 1);
		const auto z_comp = (current_vertex + 2);

        // Convert to screen space
        //*x_comp /= input_rect.right;
        //*y_comp /= input_rect.bottom;
		// or..
		*x_comp /= 1000.0f;
		*y_comp /= 1000.0f;

        // Using scale
		*x_comp *= transform_.scale_.x;
		*y_comp *= transform_.scale_.y;

		const auto original_x = *x_comp;
        // Using rotation
		*x_comp = (original_x *  cosf(transform_.rotation_)) + (*y_comp * sinf(transform_.rotation_));
		*y_comp = (original_x * -sinf(transform_.rotation_)) + (*y_comp * cosf(transform_.rotation_));

        // Finally, using translation.
		*x_comp += transform_.translation_.x / input_rect.right;
		*y_comp += transform_.translation_.y / input_rect.bottom;



		// Move to next vertext position's x.
		current_vertex += Mesh::number_of_element_per_stride;
	}
	





	mesh_.Update_VAO_VBO();
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
