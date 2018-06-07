#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "vector3.hpp"
#include "vector2.hpp"
#include "Color.h"



class Mesh
{
	friend class Object;


	std::vector<float> vertices; // Collection of vertices position and color.


	unsigned int number_of_vertex_ = 0;// number of vertecies.
	unsigned int index_ = 0;      // Index in vao.

	unsigned int primitive_ = GL_TRIANGLES;

	GLuint VBO; // ....Waste or not? GLuint or unsigned int?
	GLuint VAO; // ....Waste or not? GLuint or unsigned int?
	 

	void Emplemplace_back_vertices(const float size, const vector3 input_Positon, const Color input_Color);
public:
	static Mesh Create_Triangle(vector2 input_vector = vector2(1000.0f, 1000.0f), float size = 0.5f, Color input_color = Color(0.3f, 0.0f, 0.0f));
	static Mesh Create_Square(vector2 input_vector = vector2(1000.0f, 1000.0f), float size = 0.5f, Color input_color = Color(0.0f, 0.3f, 0.0f));
	static Mesh Create_Circle(vector2 input_vector = vector2(1000.0f, 1000.0f), float size = 0.5f, int resolution = 10, Color input_color = Color(0.0f, 0.0f, 0.3f));
	static Mesh Create_Line(vector2 input_vector = vector2(1000.0f, 1000.0f), float size = 0.5f, float angle = 0.0f, Color input_color = Color(0.3f, 0.0f, 0.0f));

	void Initialize_VAO_VBO();
	void Update_VAO_VBO();



	unsigned int Get_Index() const { return index_; };
	void Set_Index(const unsigned int input) { index_ = input; };

	unsigned int Get_Num_of_vert() const { return number_of_vertex_; };
	void Set_Num_of_vert(const unsigned int input) { number_of_vertex_ = input; };

	unsigned int Get_Primitive() const { return primitive_; };
	void Set_Primitive(const unsigned int input) { primitive_ = input; };


	unsigned int Get_VAO() const { return VAO; };

	int bytes_of_data = 0; // Size of vertices in bytes.
	static unsigned int number_of_element_per_stride;
};
