#pragma once
#include <string>
#include "Object.h"
#include <list>
#include <unordered_map>


class Font : public Object
{
	friend class Text;
	struct CharDesc
	{
		unsigned int id_;
		unsigned int x_;
		unsigned int y_;
		unsigned int width_;
		unsigned int height_;
		unsigned int xoffset_;
		unsigned int yoffset_;
		unsigned int xadvance_;
		unsigned int page_;
		//unsigned int chnl = 15;
	};

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


		std::string name_ = "EnglishFont";
		unsigned int size_ = 32;
		Common common_;
		Page page_;
	};

	Texture font_texture_;
	
	Informations info_;
	unsigned int count_ = 0;
	std::unordered_map<unsigned int, CharDesc> characters_{};

	void SetCoreInformation(const std::string input_string);
	void SetCommons(const std::string input_string);
	void SetPage(const std::string input_string);
	void SetChar(const std::string input_string);

	void GetLineSetString(std::string keyword, std::string inputline, std::string& target);
	void GetLineSetNumber(std::string keyword, std::string inputline, unsigned int& target);
public:
	unsigned int shader_ = 0;

	void Initialize(unsigned int& input_shader, std::string file_name);

	Informations GetInfos() { return info_; }
	std::unordered_map<unsigned int, CharDesc> GetCharDesc() { return characters_; };
};
