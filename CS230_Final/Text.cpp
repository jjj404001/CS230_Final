#include "Text.h"
#include <iostream>

void Text::Initialize(std::string input_string, Font& input_font)
{
	font_info_ = &input_font;
	string_ = input_string;
	for(auto i : input_string)
	{
		Mesh mesh;
		mesh = Mesh::Create_Font_Square(i, font_info_);
		Texture texture;
		texture = font_info_->font_texture_;
		

		Object obj;
		obj.mesh_ = mesh;
		obj.texture_ = texture;

		

		obj.shader = font_info_->shader_;

		text_objects_.push_back(obj);
	}

}

void Text::Update()
{
	vector2 current_position = 0.0f;
	auto current_character_object = text_objects_.begin();


	for (auto current_character_in_string : string_)
	{
		auto current_char_info = font_info_->characters_.at(current_character_in_string);

		if (current_character_object == text_objects_.end())
			break;
		else if(current_character_in_string == ' ')
		{
			current_position.x += current_char_info.xadvance_ * (*current_character_object).transform_.GetScale().x;
		}
		else if (current_character_in_string == '\t')
		{
			current_char_info = font_info_->characters_.at(' ');
			current_position.x += current_char_info.xadvance_ * 4 * (*current_character_object).transform_.GetScale().x;
		}
		else if (current_character_in_string == '\n')
		{
			current_char_info = font_info_->characters_.at(' ');
			// Reset x translation to very first of text.
			current_position.x = text_objects_.begin()->transform_.GetTranslation().x;
			current_position.y += font_info_->GetInfos().common_.lineHeight_;
		}



		auto size = vector2(current_char_info.width_, current_char_info.height_);



		


		current_position.x += current_char_info.xadvance_ * (*current_character_object).transform_.GetScale().x;
		// + current height / 2 to bond character with very bottom of line.
		(*current_character_object).transform_.SetTranslation(vector2(current_position.x - current_char_info.xoffset_, current_position.y + current_char_info.height_ /2));

		++current_character_object;
		//std::cout << i << std::endl;
	}
}
