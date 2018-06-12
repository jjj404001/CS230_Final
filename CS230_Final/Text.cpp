#include "Text.h"
#include <iostream>

void Text::Initialize(std::string input_string, Font& input_font, RECT input_rect)
{
	font_info_ = &input_font;
	string_ = input_string;

	const auto line_height = font_info_->GetInfos().common_.lineHeight_;
	// Starting point is upper left of window.
	vector2 starting_point = { -static_cast<float>(input_rect.right),
		static_cast<float>(input_rect.bottom) - line_height };

	for(auto current_char : input_string)
	{
		auto current_char_desc = font_info_->GetCharDesc().at(current_char);
		// If current character is new line, go to next line and ignore below.
		if (current_char == '\n')
		{
			starting_point.x = 0.0f;
			starting_point.y -= line_height;
			

			//ignore below.
			continue;
		}
		// else If current character is tab, make space * 4 and ignore below.
		else if (current_char == '\t')
		{
			auto space_width = font_info_->GetCharDesc().at(' ').xadvance_;

			starting_point.x += space_width * 4;;

			//ignore below.
			continue;
		}
		// else if character is whith space. 
		else if (current_char == L' ')
		{
			starting_point.x += current_char_desc.xadvance_;

			continue;
		}
		// Quad's size is current character's size with in font.
		const vector2 quad_size = { static_cast<float>(current_char_desc.width_)
									,static_cast<float>(current_char_desc.height_) };

		Mesh mesh;
		// If character pass all test above, add char quad to mesh.
		AddCharQuadToMesh(mesh, current_char_desc, quad_size, starting_point, Color(0.3f, 0.0f, 0.0f), line_height);
		// Load texture
		Texture texture = font_info_->font_texture_;

		// Push back builded object with calculated values.
		Object builded_object;
		builded_object.mesh_ = mesh;
		builded_object.texture_ = texture;
		builded_object.shader = font_info_->shader_;
		text_objects_.push_back(builded_object);

		// Recalculate starting point for next character.
		starting_point.x += current_char_desc.width_ + current_char_desc.xoffset_;




		
		/*mesh = Mesh::Create_Font_Square(current_char, font_info_);
		Texture texture;
		texture = font_info_->font_texture_;
		

		Object obj;
		obj.mesh_ = mesh;
		obj.texture_ = texture;

		

		obj.shader = font_info_->shader_;

		text_objects_.push_back(obj);*/
	}

}

void Text::Update(RECT input_rect)
{
	// If there is no text, do not update
	if (text_objects_.empty())
		return;


	for (auto current_char : text_objects_)
		current_char.Update(input_rect);
}





























void Text::AddCharQuadToMesh(Mesh& mesh, Font::CharDesc character, vector2 image_dimensions,
							 vector2 current_position, Color input_color, float line_height)
{
  // Get mesh's width and height from character's width and height. 
	const auto mesh_width = static_cast<float>(character.width_);
	const auto mesh_height = static_cast<float>(character.height_);
	// Calculate position of vecticies.
	vector3 top_left = { current_position.x, (mesh_height)+current_position.y, 0.0f };
	vector3 top_right = { (mesh_width)+current_position.x, (mesh_height)+current_position.y, 0.0f };
	vector3 bottom_left = { current_position.x, current_position.y, 0.0f };
	vector3 bottom_right = { (mesh_width)+current_position.x, current_position.y, 0.0f };

	// Add character's offset to verticies.
	top_left.x += character.xoffset_;
	top_right.x += character.xoffset_;
	bottom_left.x += character.xoffset_;
	bottom_right.x += character.xoffset_;


	// Add character's height using line height, yoffset, and character's height.
	top_left.y += line_height - (character.yoffset_ + character.height_);
	top_right.y += line_height - (character.yoffset_ + character.height_);
	bottom_left.y += line_height - (character.yoffset_ + character.height_);
	bottom_right.y += line_height - (character.yoffset_ + character.height_);


	// Texture coordinate
	const auto u_0 = static_cast<float>(character.x_ / image_dimensions.x);
	const auto v_0 = static_cast<float>(character.y_ / image_dimensions.y);

	const auto u_1 = static_cast<float>(character.x_ + character.width_) / image_dimensions.x;
	const auto v_1 = static_cast<float>(character.y_ + character.height_) / image_dimensions.y;


	// First Triangle
	// 1st vert
	mesh.AddPoint(bottom_left);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_0, v_1 , 0.0f });
	// 2nd vert
	mesh.AddPoint(bottom_right);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_1, v_1 , 0.0f });
	// 3rd vert
	mesh.AddPoint(top_right);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_1, v_0 , 0.0f });

	// Second Triangle
	// 1st vert
	mesh.AddPoint(top_right);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_1, v_0 , 0.0f });

	// 2nd vert
	mesh.AddPoint(top_left);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_0, v_0 , 0.0f });

	// 3rd vert
	mesh.AddPoint(bottom_left);
	mesh.AddColor(input_color);
	mesh.AddPoint({ u_0, v_1 , 0.0f });
	
	


	mesh.number_of_vertex_ = 6; // square = 6 vertecies.
	mesh.Initialize_VAO_VBO();



	mesh.bytes_of_data = static_cast<unsigned int>(mesh.vertices.size()) * sizeof(float);
	mesh.primitive_ = GL_TRIANGLES;
}