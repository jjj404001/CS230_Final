#include "Graphics.h"
#include <iostream>


#define FIXED_INDEX 0
#define PI 3.14159265f // TODO: Duplicate with mesh file. fix it
#define TRANSLATION_FACTOR 10.0f
#define SCALE_FACTOR 1.0f
#define ROTATION_FACTOR 3.14159265f *2.0f / 20.0f

void Graphics::Initialize()
{
	//SetUpShader(shader_program_POS_BLACK, VERT_SOURCE_POSITION, FRAG_SOURCE_COLOR_BLACK);
	//SetUpShader(shader_program_POS_RED, VERT_SOURCE_POSITION, FRAG_SOURCE_COLOR_RED);
	SetUpShader(shader_program_POS_COLOR, VERT_SOURCE_COLOR_INPUT, FRAG_SOURCE_COLOR_INPUT);
	SetUpShader(shader_program_POS_TEX, VERT_SOURCE_TEXTURE_POS, FRAG_SOURCE_TEXTURE_POS);


	Object o1;
	o1.mesh_ = Mesh::Create_Triangle(100.0f);
	o1.texture_.LoadFromImageFile("Texture/EnglishFont_0.png");
	Object o2;
	o2.mesh_ = Mesh::Create_Square(200.0f);
	o2.texture_.LoadFromImageFile("Texture/EnglishFont_0.png");
	Object o3;
	o3.mesh_ = Mesh::Create_Circle(300.0f, 50);
	o3.texture_.LoadFromImageFile("Texture/EnglishFont_0.png");
	Object o4;
	o4.mesh_ = Mesh::Create_Line(2000.0f, 0.0f);
	o4.texture_.LoadFromImageFile("Texture/EnglishFont_0.png");

	Object o5;
	o5.mesh_ = Mesh::Create_Square(vector2(700.0f, 900.0f));
	o5.texture_.LoadFromImageFile("Texture/test_texture.png");

	AddObject(o1, shader_program_POS_COLOR);
	AddObject(o2, shader_program_POS_COLOR);
	AddObject(o3, shader_program_POS_COLOR);
	AddObject(o4, shader_program_POS_COLOR);
	AddObject(o5, shader_program_POS_COLOR);
}


void Graphics::Update()
{

	for (auto current_object : objects_list)
	{
		current_object.Update(rect_);
		if (current_object.texture_.GetTextureData() != NULL)
			glBindTexture(GL_TEXTURE_2D, current_object.texture_.GetTextureData());
		glUseProgram(current_object.shader);

		

		glBindVertexArray(current_object.mesh_.Get_VAO());
		glDrawArrays(current_object.mesh_.Get_Primitive(), FIXED_INDEX, current_object.mesh_.Get_Num_of_vert());
	}
}

void Graphics::AddObject(Object input_object, unsigned int input_shader)
{
	input_object.shader = input_shader;
	objects_list.emplace_back(input_object);
	objects_list.back().mesh_.Set_Index(current_index_of_mesh);
	current_index_of_mesh += objects_list.back().mesh_.Get_Num_of_vert();
}

void Graphics::MoveEverything()
{
	std::cout << "!!Graphics::MoveEverything" << std::endl;
	for(auto& i : objects_list)
	{
		i.transform_.translation_.y += 1.0f;
	}
}

void Graphics::ScaleEverything()
{
	std::cout << "!!Graphics::ScaleEverything" << std::endl;
	for (auto& i : objects_list)
	{
		i.transform_.scale_ *= 1.1f;
	}
}

void Graphics::RotateEverything()
{
	std::cout << "!!Graphics::RotateEverything" << std::endl;
	for (auto& current_object : objects_list)
	{
		current_object.transform_.rotation_ += 0.1f;
		std::cout << current_object.transform_.rotation_ << std::endl;
	}
}

void Graphics::MoveSelected(Object* input_object, vector2 translation_input)
{
	std::cout << "!!Graphics::MoveSelected" << std::endl;

	input_object->transform_.translation_ += translation_input * TRANSLATION_FACTOR;
}

void Graphics::ScaleSelected(Object* input_object, vector2 translation_input)
{
	std::cout << "!!Graphics::ScaleSelected" << std::endl;

	translation_input.x /= 10.0f;
	translation_input.y /= 10.0f;

	input_object->transform_.scale_.x += translation_input.x *SCALE_FACTOR;
	input_object->transform_.scale_.y += translation_input.y *SCALE_FACTOR;
}

void Graphics::RotateSelected(Object* input_object, vector2 translation_input)
{
	std::cout << "!!Graphics::RotateSelected" << std::endl;
	// ONLY WORKS WITH HORIZONTAL ARROW.
	input_object->transform_.rotation_ += translation_input.x * ROTATION_FACTOR;
}


void Graphics::SetUpShader(unsigned int& input_shader_program, const char* input_vertext_source, const char*  input_fragment_source)
{
	if (vertex_shader_source != input_vertext_source)
		vertex_shader_source = input_vertext_source;
	else
		return;

	if (fragment_shader_source != input_fragment_source)
		fragment_shader_source = input_fragment_source;
	else
		return;


	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);



	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "Error!! Vertex shader compile failed. : \n" << infoLog << std::endl;
	}




	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);


	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "Error!! Fragment shader compile failed. : \n" << infoLog << std::endl;
	}


	input_shader_program = glCreateProgram();
	glAttachShader(input_shader_program, vertex_shader);
	glAttachShader(input_shader_program, fragment_shader);
	glLinkProgram(input_shader_program);

	glGetProgramiv(input_shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(input_shader_program, 512, NULL, infoLog);
		std::cout << "Error!! Shader program link failed. : \n" << infoLog << std::endl;
	}

	glUseProgram(input_shader_program);

	glDetachShader(input_shader_program, vertex_shader);
	glDetachShader(input_shader_program, fragment_shader);

	glDeleteShader(vertex_shader);   // delete shaders after make program.
	glDeleteShader(fragment_shader); // delete shaders after make program.
}
