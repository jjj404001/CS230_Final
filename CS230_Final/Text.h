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
	void Initialize(std::string input_string, Font& input_font, RECT input_rect);
	void Update(RECT input_rect);

	static void AddCharQuadToMesh(Mesh& mesh, Font::CharDesc character, vector2 image_dimensions,
									vector2 current_position, Color input_color, float line_height);
};