#include "Texture.h"
#include <GL/glew.h>
#include <iostream>



void Texture::LoadFromImage(std::string file_name)
{
	glGenTextures(1, &texture_);
	glBindTexture(GL_TEXTURE_2D, texture_);

	// Set filtering options.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load texture from image
	if (!image_.LoadFromPNG_File(file_name))
		std::cout << "Fail to load image from file!" << std::endl;


	// Generate texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_.width_, image_.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, image_.data_);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image_.data_);
}
