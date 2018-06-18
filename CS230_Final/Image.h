#pragma once
#include <string>
#include <vector>
#include "Color.h"


class Image
{
	friend class Texture;
	using ImageData = unsigned char*;


	std::vector<Color> pixels{};
	ImageData data_ = nullptr;
	int width_ = 0;
	int height_ = 0;
	int number_of_channel_ = 0; // number of channel. If image's channel format is RGBA, 4.

public:
	bool LoadFromPNG_File(std::string file_name);
	bool SaveToPNG_File(std::string file_name);


	void ResizeToPixelWidthHeight(int input_width, int input_height);
	void FlipVertically();

	ImageData* GetPixelData() { return &data_; }
	Color* GetPixelsPointer() { return &pixels[0]; };
	int GetPixelsBufferBytesSize() { return static_cast<int>(pixels.size() * sizeof(Color)); }

	int GetWidth() { return width_; }
	int GetHeight() { return height_; }
	int GetNumberOfChannel() { return number_of_channel_; }

	void SetWidth(int input) { width_ = input; }
	void SetHeight(int input) { height_ = input; }
	void SetNumberOfChannel(int input) { number_of_channel_ = input; }
};
