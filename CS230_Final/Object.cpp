#include "Object.h"
#include "Camera.h"
#include <iostream>
#define STANDARD 1000.0f

// TODO : after check, implement with ndc.
void Object::Update(Camera input_rect)
{
	// Loop through every vertecies.
	{
		auto current_vertex = mesh_.vertices.begin();
		while (current_vertex != mesh_.vertices.end())
		{
			const auto x_comp = current_vertex;
			const auto y_comp = (current_vertex + 1);
			const auto z_comp = (current_vertex + 2);

			



			// Move to next vertext position's x.
			current_vertex += Mesh::number_of_element_per_stride;
		}
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
