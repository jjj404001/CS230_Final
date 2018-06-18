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
	stbi_write_png("ScreenShot.png", width_, height_, number_of_channel_, &pixels[0], sizeof(Color) * width_);

	return true;
}

void Image::ResizeToPixelWidthHeight(int input_width, int input_height)
{ 
	const size_t newSize = (input_width * input_height);
	width_ = static_cast<int>(input_width);
	height_ = static_cast<int>(input_height);
	pixels.resize(newSize);
}

void Image::FlipVertically()
{
	if (pixels.empty())
		return;


	std::vector<Color> temp{};

	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			temp.push_back(pixels.at(((height_ - i - 1) * width_) + j));
		}
	}
	pixels = temp;
}