#include "Font.h"
#include <fstream>
#include <iostream>
#define MAX_LINE 255

void Font::Initialize(unsigned int& input_shader)
{
	std::ifstream file("Texture/EnglishFont.fnt");
	char input_string[MAX_LINE];
	std::string line;

	// Loop untill line reaches the end.
	while (!file.eof())
	{
		file >> line; // Get keyword from opened file.
		if (line == "kerning") // ...What is kerning?
			break;



		file.getline(input_string, MAX_LINE); // Get one line from open file.


		if (line == "info")
			SetCoreInformation(input_string);
		else if (line == "common")
			SetCommons(input_string);
		else if (line == "page")
			SetPage(input_string);
		else if (line == "char")
			SetChar(input_string);

	}

	font_texture_.LoadFromImageFile("Texture/" + info_.page_.file_);

	shader_ = input_shader;


	file.close();
}

void Font::SetCoreInformation(const std::string input_string)
{
	GetLineSetString("face", input_string, info_.name_);
	GetLineSetNumber("size", input_string, info_.size_);
}

void Font::SetCommons(const std::string input_string)
{
	GetLineSetNumber("lineHeight", input_string, info_.common_.lineHeight_);
	GetLineSetNumber("base", input_string, info_.common_.base_);
	GetLineSetNumber("scaleW", input_string, info_.common_.scaleW_);
	GetLineSetNumber("scaleH", input_string, info_.common_.scaleH_);
	GetLineSetNumber("pages", input_string, info_.common_.pages_);
}

void Font::SetPage(const std::string input_string)
{
	GetLineSetNumber("pages", input_string, info_.page_.id_);
	GetLineSetString("file", input_string, info_.page_.file_);
}

void Font::SetChar(const std::string input_string)
{
	// char id=32   x=84    y=38    width=3     height=1     xoffset=-1    yoffset=31    xadvance=8     page=0  chnl=15
	CharDesc current_char;
	GetLineSetNumber("id", input_string, current_char.id_);
	GetLineSetNumber("x", input_string, current_char.x_);
	GetLineSetNumber("y", input_string, current_char.y_);
	GetLineSetNumber("width", input_string, current_char.width_);
	GetLineSetNumber("height", input_string, current_char.height_);
	GetLineSetNumber("xoffset", input_string, current_char.xoffset_);
	GetLineSetNumber("yoffset", input_string, current_char.yoffset_);
	GetLineSetNumber("xadvance", input_string, current_char.xadvance_);

	characters_.insert_or_assign(current_char.id_, current_char );
}

void Font::GetLineSetString(std::string keyword, std::string inputline, std::string& target)
{
	keyword += "=\"";
	auto offset = inputline.find(keyword);

	if (offset != std::wstring::npos)
	{
		offset += keyword.length();
		const auto end = inputline.find("\"", offset);
		target = inputline.substr(offset, end - offset);
	}
}

void Font::GetLineSetNumber(std::string keyword, std::string inputline, unsigned int& target)
{
	auto searchResult = inputline.find(keyword + '=');


	if (searchResult != std::wstring::npos)
	{
		searchResult += keyword.length() + 1;
		const auto end = inputline.find(L' ', searchResult);
		const auto resultLength = end - searchResult;
		const auto stringToConvert = inputline.substr(searchResult, resultLength);

		target = static_cast<unsigned int>(std::stoi(stringToConvert));
	}
}
