#pragma once
#include <string>
#include "Color.h"

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
	bool SaveToPNG_File(std::string file_name);

	template<typename Number>
	void ResizeToPixelWidthHeight(Number width, Number height) { width_ = static_cast<int>(width); height_ = static_cast<int>(height); }
	ImageData* GetPixelsPointer() { return &data_; }
	int GetPixelsBufferBytesSize() { return static_cast<int>(width_ * height_ * sizeof(Color)); }

	int GetWidth() { return width_; }
	int GetHeight() { return height_; }
	int GetNumberOfChannel() { return number_of_channel_; }
};
