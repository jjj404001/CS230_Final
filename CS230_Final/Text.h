#pragma once
#include "Font.h"

class Camera;
class Text
{
	std::string string_;
	vector2 starting_coordinate_ = {0.0f, 0.0f};
	unsigned int line_count_ = 0;
	

public:
	Font * font_info_ = nullptr;
	std::list<Object> text_objects_;

	void SetScale(vector2 size = vector2(1.0f, 1.0f));

	void Initialize(bool is_HUD, std::string input_string, Font& input_font, Color input_color, Camera input_rect);
	void Update(Camera input_rect);

	void SetText(std::string input_string);

	static void AddCharQuadToMesh(Mesh& mesh, Font* input_font, Font::CharDesc character,
									vector2 current_position, Color input_color, float line_height);
};