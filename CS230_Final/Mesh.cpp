#include "Mesh.h"
#include "Font.h"
#include <cmath>
#define PI 3.14159265f
#define FONT_SIZE vector2(256,256)
unsigned int Mesh::number_of_element_per_stride = 10; // Position 3 + Color 4 + Texture 3

namespace Math
{
	float inversed_radian = (PI) / 180;
}

void Mesh::Emplemplace_back_whole_attrib(const float size, const vector3 input_Positon, const Color input_Color)
{
	// Position
	vertices.emplace_back(input_Positon.x);
	vertices.emplace_back(input_Positon.y);
	vertices.emplace_back(input_Positon.z);

	// Color
	vertices.emplace_back(input_Color.Red);
	vertices.emplace_back(input_Color.Green);
	vertices.emplace_back(input_Color.Blue);
	vertices.emplace_back(input_Color.Alpha);

	const auto uv = vector3{ (size / 2 + input_Positon.x) / size, (size / 2 - input_Positon.y) / size, 0.0f };
	vertices.emplace_back(uv.x);
	vertices.emplace_back(uv.y);
	vertices.emplace_back(uv.z);


	number_of_vertex_++;
}

void Mesh::Emplemplace_back_whole_attrib(const vector2 size, const vector3 input_Positon, const Color input_Color)
{
	// Position
	vertices.emplace_back(input_Positon.x);
	vertices.emplace_back(input_Positon.y);
	vertices.emplace_back(input_Positon.z);

	// Color
	vertices.emplace_back(input_Color.Red);
	vertices.emplace_back(input_Color.Green);
	vertices.emplace_back(input_Color.Blue);
	vertices.emplace_back(input_Color.Alpha);

	const auto uv = vector3{ (size.x / 2 + input_Positon.x) / size.x, (size.y / 2 - input_Positon.y) / size.y, 0.0f };
	vertices.emplace_back(uv.x);
	vertices.emplace_back(uv.y);
	vertices.emplace_back(uv.z);


	number_of_vertex_++;
}

void Mesh::Emplemplace_back_whole_attrib(const vector3 input_Positon, const Color input_Color, const vector3 input_uv)
{
	// Position
	vertices.emplace_back(input_Positon.x);
	vertices.emplace_back(input_Positon.y);
	vertices.emplace_back(input_Positon.z);

	// Color
	vertices.emplace_back(input_Color.Red);
	vertices.emplace_back(input_Color.Green);
	vertices.emplace_back(input_Color.Blue);
	vertices.emplace_back(input_Color.Alpha);

	// Texture coordinate
	vertices.emplace_back(input_uv.x);
	vertices.emplace_back(input_uv.y);
	vertices.emplace_back(input_uv.z);


	number_of_vertex_++;
}

void Mesh::Emplemplace_back_whole_attrib_UV(const char input_char, Font* input_font, const vector3 input_Positon, const Color input_Color)
{
	vector2 size = vector2(input_font->GetCharDesc().at(input_char).width_, input_font->GetCharDesc().at(input_char).height_);


	// Position
	vertices.emplace_back(input_Positon.x);
	vertices.emplace_back(input_Positon.y);
	vertices.emplace_back(input_Positon.z);

	// Color
	vertices.emplace_back(input_Color.Red);
	vertices.emplace_back(input_Color.Green);
	vertices.emplace_back(input_Color.Blue);
	vertices.emplace_back(input_Color.Alpha);

	auto uv = vector3{ (size.x / 2 + input_Positon.x) / size.x, (size.y / 2 + input_Positon.y) / size.y, 0.0f };

	

	uv.x += input_font->GetCharDesc().at(input_char).x_ ;
	uv.x /= input_font->GetInfos().common_.scaleW_;
	uv.y += input_font->GetCharDesc().at(input_char).y_;
	uv.y /= input_font->GetInfos().common_.scaleW_;

	vertices.emplace_back(uv.x);
	vertices.emplace_back(uv.y);
	vertices.emplace_back(uv.z);


	number_of_vertex_++;
}


//TODO: Apply ndc
Mesh Mesh::Create_Triangle(float size, Color input_color)
{
	Mesh tri;


	const auto bottom_left  = vector3{-size / 2, -size / 2, 0.0f};
	const auto bottom_right = vector3{size / 2, -size / 2, 0.0f};
	const auto top_middle   = vector3{0.0f, size / 2, 0.0f};


	tri.Emplemplace_back_whole_attrib(size, bottom_left, input_color);
	tri.Emplemplace_back_whole_attrib(size, bottom_right, input_color);
	tri.Emplemplace_back_whole_attrib(size, top_middle, input_color);


	tri.Initialize_VAO_VBO();


	tri.bytes_of_data     = static_cast<unsigned int>(tri.vertices.size()) * sizeof(float);
	tri.primitive_        = GL_TRIANGLES;

	return tri;
}

//TODO : fix below with vertex.

Mesh Mesh::Create_Square(float size, Color input_color)
{
	Mesh square;

	const auto bottom_left  = vector3(-size / 2, -size / 2, 0.0f);
	const auto bottom_right = vector3(size / 2, -size / 2, 0.0f);
	const auto top_right    = vector3(size / 2, size / 2, 0.0f);
	const auto top_left     = vector3(-size / 2, size / 2, 0.0f);



	square.Emplemplace_back_whole_attrib(size, bottom_left, input_color);
	square.Emplemplace_back_whole_attrib(size, bottom_right, input_color);
	square.Emplemplace_back_whole_attrib(size, top_right, input_color);

	square.Emplemplace_back_whole_attrib(size, top_right, input_color);
	square.Emplemplace_back_whole_attrib(size, top_left, input_color);
	square.Emplemplace_back_whole_attrib(size, bottom_left, input_color);


	square.Initialize_VAO_VBO();



	square.bytes_of_data     = static_cast<unsigned int>(square.vertices.size()) * sizeof(float);
	square.primitive_        = GL_TRIANGLES;

	return square;
}

Mesh Mesh::Create_Square(vector2 size, Color input_color)
{
	Mesh square;

	const auto bottom_left = vector3(-size.x / 2, -size.y / 2, 0.0f);
	const auto bottom_right = vector3(size.x / 2, -size.y / 2, 0.0f);
	const auto top_right = vector3(size.x / 2, size.y / 2, 0.0f);
	const auto top_left = vector3(-size.x / 2, size.y / 2, 0.0f);



	square.Emplemplace_back_whole_attrib(size, bottom_left, input_color);
	square.Emplemplace_back_whole_attrib(size, bottom_right, input_color);
	square.Emplemplace_back_whole_attrib(size, top_right, input_color);

	square.Emplemplace_back_whole_attrib(size, top_right, input_color);
	square.Emplemplace_back_whole_attrib(size, top_left, input_color);
	square.Emplemplace_back_whole_attrib(size, bottom_left, input_color);


	square.Initialize_VAO_VBO();



	square.bytes_of_data = static_cast<unsigned int>(square.vertices.size()) * sizeof(float);
	square.primitive_ = GL_TRIANGLES;

	return square;
}


Mesh Mesh::Create_Circle(float size, int resolution, Color input_color)
{
	Mesh circle;

	auto i = 0;
	const auto angle = 360.0f / resolution * Math::inversed_radian;

	// Point in origin.
	circle.Emplemplace_back_whole_attrib(size, vector3(0.0f, 0.0f, 0.0f), input_color);
	while (i <= resolution)
	{
		const auto x = cosf(i * angle) * size / 2;
		const auto y = sinf(i * angle) * size / 2;

		const auto current_vertex = vector3(x, y, 0.0f);



		circle.Emplemplace_back_whole_attrib(size, current_vertex, input_color);
		i++;
	}




	circle.Initialize_VAO_VBO();


	circle.bytes_of_data = static_cast<unsigned int>(circle.vertices.size()) * sizeof(float);
	circle.primitive_ = GL_TRIANGLE_FAN;

	return circle;
}

Mesh Mesh::Create_Line(float size, float angle, Color input_color)
{
	Mesh line;

	auto x = cosf(angle) * size / 2;
	auto y = sinf(angle) * size / 2;
	const auto start = vector3(x, y, 0.0f);

	x = cos(angle + PI) * size / 2;
	y = sin(angle + PI) * size / 2;
	const auto end   = vector3(x, y, 0.0f);


	line.Emplemplace_back_whole_attrib(size, start, input_color);
	line.Emplemplace_back_whole_attrib(size, end, input_color);



	line.Initialize_VAO_VBO();


	line.bytes_of_data     = static_cast<unsigned int>(line.vertices.size()) * sizeof(float);
	line.primitive_        = GL_LINE_STRIP;

	return line;
}

Mesh Mesh::Create_Font_Square(const char input_char, Font* input_font, Color input_color)
{
	Mesh square;
	const auto current_char_desc = input_font->GetCharDesc().at(input_char);
	vector2 size = vector2(input_font->GetCharDesc().at(input_char).width_, input_font->GetCharDesc().at(input_char).height_);

	const auto bottom_left = vector3(-size.x / 2, -size.y / 2, 0.0f);
	const auto bottom_right = vector3(size.x / 2, -size.y / 2, 0.0f);
	const auto top_right = vector3(size.x / 2, size.y / 2, 0.0f);
	const auto top_left = vector3(-size.x / 2, size.y / 2, 0.0f);

	

	// Position
	square.vertices.emplace_back(bottom_left.x);
	square.vertices.emplace_back(bottom_left.y);
	square.vertices.emplace_back(bottom_left.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	auto uv = vector3{ 0.0f, 1.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_ + current_char_desc.height_) / input_font->GetInfos().common_.scaleH_;



	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);



	// Position
	square.vertices.emplace_back(bottom_right.x);
	square.vertices.emplace_back(bottom_right.y);
	square.vertices.emplace_back(bottom_right.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	uv = vector3{ 1.0f, 1.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_ + current_char_desc.width_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_ + current_char_desc.height_) / input_font->GetInfos().common_.scaleH_;

	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);




	// Position
	square.vertices.emplace_back(top_right.x);
	square.vertices.emplace_back(top_right.y);
	square.vertices.emplace_back(top_right.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	uv = vector3{ 1.0f, 0.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_ + current_char_desc.width_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_) / input_font->GetInfos().common_.scaleH_;

	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);







	// Position
	square.vertices.emplace_back(top_right.x);
	square.vertices.emplace_back(top_right.y);
	square.vertices.emplace_back(top_right.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	uv = vector3{ 1.0f, 0.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_ + current_char_desc.width_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_) / input_font->GetInfos().common_.scaleH_;

	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);




	// Position
	square.vertices.emplace_back(top_left.x);
	square.vertices.emplace_back(top_left.y);
	square.vertices.emplace_back(top_left.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	uv = vector3{ 0.0f, 0.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_) / input_font->GetInfos().common_.scaleH_;

	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);




	// Position
	square.vertices.emplace_back(bottom_left.x);
	square.vertices.emplace_back(bottom_left.y);
	square.vertices.emplace_back(bottom_left.z);

	// Color
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);

	uv = vector3{ 0.0f, 1.0f, 0.0f };
	uv.x = static_cast<float>(current_char_desc.x_) / input_font->GetInfos().common_.scaleW_;
	uv.y = static_cast<float>(current_char_desc.y_ + current_char_desc.height_) / input_font->GetInfos().common_.scaleH_;


	square.vertices.emplace_back(uv.x);
	square.vertices.emplace_back(uv.y);
	square.vertices.emplace_back(uv.z);





	square.number_of_vertex_ = 6;
	square.Initialize_VAO_VBO();



	square.bytes_of_data = static_cast<unsigned int>(square.vertices.size()) * sizeof(float);
	square.primitive_ = GL_TRIANGLES;

	return square;
}

void Mesh::AddPoint(vector2 input_vector)
{
	vertices.emplace_back(input_vector.x);
	vertices.emplace_back(input_vector.y);
}

void Mesh::AddPoint(vector3 input_vector)
{
	vertices.emplace_back(input_vector.x);
	vertices.emplace_back(input_vector.y);
	vertices.emplace_back(input_vector.z); // Maybe always 0.0f
}

void Mesh::Initialize_VAO_VBO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	


	glGenBuffers(1, &VBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bytes_of_data, &vertices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, static_cast<void*>(0));


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, reinterpret_cast<void*>(sizeof(float) * 3));// Works?


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, reinterpret_cast<void*>(sizeof(float) * 7));// Works?
}

void Mesh::Update_VAO_VBO()
{
	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bytes_of_data, &vertices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, static_cast<void*>(0));


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, reinterpret_cast<void*>(sizeof(float) * 3));// Works?


	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * Mesh::number_of_element_per_stride, reinterpret_cast<void*>(sizeof(float) * 7));// Works?
}