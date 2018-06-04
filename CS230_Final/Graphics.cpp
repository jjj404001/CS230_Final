#include "Graphics.h"
#include <iostream>

#define FIXED_INDEX 0

void Graphics::Initialize()
{
	SetUpShader(vertex_shader_source, fragment_shader_source);
	Object o1;
	o1.mesh_ = Mesh::Create_Triangle();
	Object o2;
	o2.mesh_ = Mesh::Create_Square(0.4f);
	Object o3;
	o3.mesh_ = Mesh::Create_Circle(100.0f, 50);
	Object o4;
	o4.mesh_ = Mesh::Create_Line(1.0f, 0.1f);

	AddObject(o1);
	AddObject(o2);
	AddObject(o3);
	AddObject(o4);
}


void Graphics::Update()
{

	for (auto i : objects_list)
	{
		i.Update(rect_);

		glUseProgram(shader_program);
		glBindVertexArray(i.mesh_.Get_VAO());
		glDrawArrays(i.mesh_.Get_Primitive(), FIXED_INDEX, i.mesh_.Get_Num_of_vert());
	}
}

void Graphics::AddObject(Object input_object)
{
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


void Graphics::SetUpShader(const char* input_vertext_source, const char*  input_fragment_source)
{
	if (vertex_shader_source != input_vertext_source)
		vertex_shader_source = input_vertext_source;

	if (fragment_shader_source != input_fragment_source)
		fragment_shader_source = input_fragment_source;


	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
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
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);


	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "Error!! Fragment shader compile failed. : \n" << infoLog << std::endl;
	}


	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "Error!! Shader program link failed. : \n" << infoLog << std::endl;
	}

	glUseProgram(shader_program);
	glDeleteShader(vertex_shader);   // delete shaders after make program.
	glDeleteShader(fragment_shader); // delete shaders after make program.
}
