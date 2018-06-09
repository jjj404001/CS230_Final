#include "Text.h"
#include <iostream>

void Text::Initialize(std::string input_string, Font& input_font)
{
	font_info_ = &input_font;
	string_ = input_string;
	vector2 current_position = starting_coordinate_;
	for(auto i : input_string)
	{
		Transform transform;
		transform.SetTranslation(current_position);


		auto size = vector2(font_info_->characters_.at(i).width_, font_info_->characters_.at(i).height_);

		Mesh mesh;
		mesh = Mesh::Create_Font_Square(i, font_info_, size);


		Texture texture;
		texture = font_info_->font_texture_;
		


		Object obj;
		obj.transform_ = transform;
		obj.mesh_ = mesh;
		obj.texture_ = texture;

		obj.transform_.SetScale(vector2(10.0f, 10.0f));

		obj.shader = font_info_->shader_;

		text_objects_.push_back(obj);


		current_position.x += font_info_->characters_.at(i).xadvance_;
		std::cout << i << std::endl;
	}

}

void Text::Update()
{
	vector2 current_position = 0.0f;
	auto current_character = text_objects_.begin();
	for (auto i : string_)
	{
		auto size = vector2(font_info_->characters_.at(i).width_, font_info_->characters_.at(i).height_);

		


		current_position.x += font_info_->characters_.at(i).xadvance_ * (*current_character).transform_.GetScale().x;

		(*current_character).transform_.SetTranslation(current_position);

		++current_character;
		std::cout << i << std::endl;
	}
}
