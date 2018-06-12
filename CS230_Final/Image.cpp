#define STB_IMAGE_IMPLEMENTATION // Important.
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#include "stb_image.h"
#include "stb_image_write.h"
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

bool Image::SaveToPNG_File(std::string file_name)
{
	stbi_write_png("ScreenShot.png", width_, height_, number_of_channel_, data_, sizeof(Color) * width_);

	return true;
}
