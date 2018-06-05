#include "Object.h"
#include <iostream>

// TODO : after check, implement with ndc.
void Object::Update(RECT input_rect)
{
	// Loop through every vertecies.
	for (auto& current_mesh : mesh_.vertices)
	{
		// Looks cool
		/*i.x = (i.x * cosf(transform_.rotation_))  + (i.y * sinf(transform_.rotation_));
		i.x *= transform_.scale_;
		i.x += transform_.translation_.x / input_rect.right;

		i.y = (i.x * -sinf(transform_.rotation_)) + (i.y * cosf(transform_.rotation_));
		i.y *= transform_.scale_;
		i.y += transform_.translation_.y / input_rect.bottom;*/

		

		
		current_mesh.x *= transform_.scale_.x;
		current_mesh.y *= transform_.scale_.y;

		auto original_x = current_mesh.x;

		current_mesh.x = (original_x *  cosf(transform_.rotation_)) + (current_mesh.y * sinf(transform_.rotation_));
		current_mesh.y = (original_x * -sinf(transform_.rotation_)) + (current_mesh.y * cosf(transform_.rotation_));

		current_mesh.x += transform_.translation_.x / input_rect.right;
		current_mesh.y += transform_.translation_.y / input_rect.bottom;


		//i.z = 0.0f; ?? Dont need to
	}



	mesh_.Update_VAO_VBO();
}
