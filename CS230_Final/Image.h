#pragma once

#include <string>
#include "stb_image.h"
#include "stb_image_write.h"

class Image
{
	friend class Texture;
	using ImageData = unsigned char*;


	ImageData data_ = nullptr;
	int width_ = 0; 
	int height_ = 0;
	int number_of_channel_ = 0; // number of channel. If image's channel format is RGBA, 4.

public:
	bool LoadFromPNG_File(std::string file_name);
};