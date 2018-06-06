#pragma once
#include <string>
#include "Image.h"


class  Texture
{
	using TextureData = unsigned int;

	TextureData texture_ = 0;
	Image image_;


public: 
	void LoadFromImage(std::string file_name);
};
