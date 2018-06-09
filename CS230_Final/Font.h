#pragma once
#include <string>
#include "Object.h"
#include <list>


class Font : public Object
{
	struct Informations
	{
		struct Common
		{
			unsigned int lineHeight_ = 32;
			unsigned int base_ = 26;
			unsigned int scaleW_ = 256;
			unsigned int scaleH_ = 256;
			unsigned int pages_ = 1;
		};
		struct Page
		{
			unsigned int id_ = 0;
			std::string file_ = "EnglishFont_0.png";
		};


		struct CharDesc
		{
			unsigned int id_ = 32;
			unsigned int x_ = 84;
			unsigned int y_ = 38;
			unsigned int width_ = 3;
			unsigned int height_ = 1;
			unsigned int xoffset_ = -1;
			unsigned int yoffset_ = 31;
			unsigned int xadvance_ = 8;
			unsigned int page_ = 0;
			//unsigned int chnl = 15;
		};
		std::string name_ = "EnglishFont";
		unsigned int size_ = 32;
		Common common_;
		Page page_;
		std::list<CharDesc> char_descriptions_;
	};
	
	Informations info;

	unsigned int count = 0;

	void SetCoreInformation(const std::string input_string);
	void SetCommons(const std::string input_string);
	void SetPage(const std::string input_string);
	void GetLineSetString(std::string keyword, std::string inputline, std::string& target);
	void GetLineSetNumber(std::string keyword, std::string inputline, unsigned int& target);
public:
	void Initialize();

	void CharDesc(const std::string input_string);
};
