#pragma once
#include <vector>
#include <GL/glew.h>
#include <GL/wglew.h>
#include "vector3.hpp"
#include "vector2.hpp"
#include "Color.h"


class Font;

class Mesh
{
	friend class Object;
	friend class Text;


	std::vector<float> vertices; // Collection of vertices position and color.


	unsigned int number_of_vertex_ = 0;// number of vertecies.
	unsigned int index_ = 0;      // Index in vao.

	unsigned int primitive_ = GL_TRIANGLES;

	GLuint VBO; // ....Waste or not? GLuint or unsigned int?
	GLuint VAO; // ....Waste or not? GLuint or unsigned int?
	 

	void Emplemplace_back_whole_attrib(const float size, const vector3 input_Positon, const Color input_Color);
	void Emplemplace_back_whole_attrib(const vector2 size, const vector3 input_Positon, const Color input_Color);
	void Emplemplace_back_whole_attrib(const vector3 input_Positon, const Color input_Color, const vector3 input_uv);
	void Emplemplace_back_whole_attrib_UV(const char input_char, Font* input_font, const vector3 input_Positon, const Color input_Color);
public:
	static Mesh Create_Triangle(float size = 100.0f, Color input_color = Color(255, 255, 255));
	static Mesh Create_Square(float size = 100.0f, Color input_color = Color(255, 255, 255));
	static Mesh Create_Square(vector2 size = vector2(100.0f), Color input_color = Color(255, 255, 255));
	static Mesh Create_Circle(float size = 100.0f, int resolution = 10, Color input_color = Color(255, 255, 255));
	static Mesh Create_Line(float size = 100.0f, float angle = 0.0f, Color input_color = Color(255, 255, 255));
	static Mesh Create_Font_Square(const char input_char, Font* input_font, Color input_color = Color(255, 255, 255));

	void AddPoint(vector2 input_vector);
	void AddPoint(vector3 input_vector);
	void AddColor(Color input_color);

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
