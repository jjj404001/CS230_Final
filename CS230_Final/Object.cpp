#include "Object.h"
#include <iostream>

// TODO : after check, implement with ndc.
void Object::Update(RECT input_rect)
{
	// Loop through every vertecies.
	for (auto& i : mesh_.vertices)
	{
		// Looks cool
		/*i.x = (i.x * cosf(transform_.rotation_))  + (i.y * sinf(transform_.rotation_));
		i.x *= transform_.scale_;
		i.x += transform_.translation_.x / input_rect.right;

		i.y = (i.x * -sinf(transform_.rotation_)) + (i.y * cosf(transform_.rotation_));
		i.y *= transform_.scale_;
		i.y += transform_.translation_.y / input_rect.bottom;*/

		auto original_x = i.x;

		i.x = (i.x * cosf(transform_.rotation_))  + (i.y * sinf(transform_.rotation_));
		i.x *= transform_.scale_;
		i.x += transform_.translation_.x / input_rect.right;

		i.y = (original_x * -sinf(transform_.rotation_)) + (i.y * cosf(transform_.rotation_));
		i.y *= transform_.scale_;
		i.y += transform_.translation_.y / input_rect.bottom;


		//i.z = 0.0f; ?? Dont need to
	}



	mesh_.Update_VAO_VBO();
}
