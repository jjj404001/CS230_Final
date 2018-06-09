#include "Font.h"
#include <fstream>
#include <iostream>
#define MAX_LINE 255

void Font::Initialize()
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

	}

	file.close();
}

void Font::SetCoreInformation(const std::string input_string)
{
	GetLineSetString("face", input_string, info.name_);
	GetLineSetNumber("size", input_string, info.size_);
}

void Font::SetCommons(const std::string input_string)
{
	GetLineSetNumber("lineHeight", input_string, info.common_.lineHeight_);
	GetLineSetNumber("base", input_string, info.common_.base_);
	GetLineSetNumber("scaleW", input_string, info.common_.scaleW_);
	GetLineSetNumber("scaleH", input_string, info.common_.scaleH_);
	GetLineSetNumber("pages", input_string, info.common_.pages_);
}

void Font::SetPage(const std::string input_string)
{
	unsigned int id = 0;
	std::string file = "EnglishFont_0.png";
	GetLineSetNumber("pages", input_string, info.page_.id_);
	GetLineSetString("file", input_string, info.page_.file_);
}

void Font::GetLineSetString(std::string keyword, std::string inputline, std::string& target)
{
	keyword += "=\"";
	auto offset = inputline.find(keyword);
	std::cout << keyword[offset] << std::endl;
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
