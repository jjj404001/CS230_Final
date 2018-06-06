#pragma once
#define RGBA32 unsigned int
#define ColorChannel float

struct Color
{
	ColorChannel Red;
	ColorChannel Green;
	ColorChannel Blue;
	ColorChannel Alpha;

	Color(ColorChannel input_R, ColorChannel input_G, ColorChannel input_B, ColorChannel input_A = 255)
		: Red(input_R), Green(input_G), Blue(input_B), Alpha(input_A) {}
};