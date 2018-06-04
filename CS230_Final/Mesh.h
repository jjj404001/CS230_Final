#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "vector3.hpp"
#define VERT_SOURCE R"(
							#version 330 core
							layout(location = 0) in vec3 aPos;
							void main()
							{
								gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
							}
							)"
#define FRAG_SOURCE R"(
								#version 330 core
								out vec4 FragColor;

								void main()
								{
									FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
								} 
								)"



class Mesh
{
	friend class Object;


	std::vector<vector3> vertices; // Collection of vertices.
	const char * vertex_shader_source = VERT_SOURCE;  // Shader sources.
	const char * fragment_shader_source = FRAG_SOURCE;

	unsigned int number_of_vertex_ = 0;// number of vertecies.
	unsigned int index_ = 0;      // Index in vao.

	unsigned int primitive_ = GL_TRIANGLES;

	GLuint VBO; // ....Waste or not? GLuint or unsigned int?
	GLuint VAO; // ....Waste or not? GLuint or unsigned int?
	 

public:
	static Mesh Create_Triangle(float size = 0.5f);
	static Mesh Create_Square(float size = 0.5f);
	static Mesh Create_Circle(float size = 0.5f, int resolution = 10);
	static Mesh Create_Line(float size = 0.5f, float angle = 0.0f);

	void Initialize_VAO_VBO();
	void Update_VAO_VBO();



	unsigned int Get_Index() const { return index_; };
	void Set_Index(const unsigned int input) { index_ = input; };

	unsigned int Get_Num_of_vert() const { return number_of_vertex_; };
	void Set_Num_of_vert(const unsigned int input) { number_of_vertex_ = input; };

	unsigned int Get_Primitive() const { return primitive_; };
	void Set_Primitive(const unsigned int input) { primitive_ = input; };


	unsigned int Get_VAO() const { return VAO; };

	int bytse_of_data = 0; // Size of vertices in bytes.
};