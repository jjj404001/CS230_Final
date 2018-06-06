#define STB_IMAGE_IMPLEMENTATION // Important.

#include "Image.h"
#include <string>


bool Image::LoadFromPNG_File(std::string file_name)
{
	data_ = stbi_load(file_name.c_str(), &width_, &height_, &number_of_channel_, 0);

	if (!data_)
		return false;
	else
		return true;
}