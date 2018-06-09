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
	void Initialize(std::string input_string, Font& input_font);
	void Update();
};