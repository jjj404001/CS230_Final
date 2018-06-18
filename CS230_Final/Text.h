#pragma once
#include "Font.h"

class Text
{
	std::string string_;
	vector2 starting_coordinate_ = {0.0f, 0.0f};
	unsigned int line_count_ = 0;
	
	

public:
	Font * font_info_ = nullptr;
	std::list<Object> text_objects_;

	void SetScale(vector2 size = vector2(1.0f, 1.0f));

	void Initialize(std::string input_string, Font& input_font, Color input_color, RECT input_rect);
	void Update(RECT input_rect);

	void SetText(std::string input_string);

	static void AddCharQuadToMesh(Mesh& mesh, Font* input_font, Font::CharDesc character, vector2 image_dimensions,
									vector2 current_position, Color input_color, float line_height);
};