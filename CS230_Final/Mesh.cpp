#include "Mesh.h"
#include <cmath>
#define PI 3.14159265f

unsigned int Mesh::number_of_element_per_stride = 10; // Position 3 + Color 4 + Texture 3

namespace Math
{
	float inversed_radian = (PI) / 180;
}
//TODO: Apply ndc
Mesh Mesh::Create_Triangle(float size, Color input_color)
{
	Mesh tri;


	const auto bottom_left  = vector3{-size, -size, 0.0f};
	const auto bottom_right = vector3{size, -size, 0.0f};
	const auto top_middle   = vector3{0.0f, size, 0.0f};



	tri.vertices.emplace_back(bottom_left.x);
	tri.vertices.emplace_back(bottom_left.y);
	tri.vertices.emplace_back(bottom_left.z);
	tri.vertices.emplace_back(input_color.Red);
	tri.vertices.emplace_back(input_color.Green);
	tri.vertices.emplace_back(input_color.Blue);
	tri.vertices.emplace_back(input_color.Alpha);
	tri.vertices.emplace_back(0.0f);
	tri.vertices.emplace_back(1.0f);
	tri.vertices.emplace_back(0.0f);
	tri.number_of_vertex_++;

	tri.vertices.emplace_back(bottom_right.x);
	tri.vertices.emplace_back(bottom_right.y);
	tri.vertices.emplace_back(bottom_right.z);
	tri.vertices.emplace_back(input_color.Red);
	tri.vertices.emplace_back(input_color.Green);
	tri.vertices.emplace_back(input_color.Blue);
	tri.vertices.emplace_back(input_color.Alpha);
	tri.vertices.emplace_back(1.0f);
	tri.vertices.emplace_back(1.0f);
	tri.vertices.emplace_back(0.0f);
	tri.number_of_vertex_++;

	tri.vertices.emplace_back(top_middle.x);
	tri.vertices.emplace_back(top_middle.y);
	tri.vertices.emplace_back(top_middle.z);
	tri.vertices.emplace_back(input_color.Red);
	tri.vertices.emplace_back(input_color.Green);
	tri.vertices.emplace_back(input_color.Blue);
	tri.vertices.emplace_back(input_color.Alpha);
	tri.vertices.emplace_back(0.5f);
	tri.vertices.emplace_back(0.0f);
	tri.vertices.emplace_back(0.0f);
	tri.number_of_vertex_++;




	tri.Initialize_VAO_VBO();




	tri.bytes_of_data     = static_cast<unsigned int>(tri.vertices.size()) * sizeof(float);
	tri.primitive_        = GL_TRIANGLES;

	return tri;
}

//TODO : fix below with vertex.
/*
Mesh Mesh::Create_Square(float size, Color input_color)
{
	Mesh square;

	const auto bottom_left  = vector3(-size, -size, 0.0f);
	const auto bottom_right = vector3(size, -size, 0.0f);
	const auto top_right    = vector3(size, size, 0.0f);
	const auto top_left     = vector3(-size, size, 0.0f);



	square.vertices.emplace_back(bottom_left.x);
	square.vertices.emplace_back(bottom_left.y);
	square.vertices.emplace_back(bottom_left.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;

	square.vertices.emplace_back(bottom_right.x);
	square.vertices.emplace_back(bottom_right.y);
	square.vertices.emplace_back(bottom_right.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;

	square.vertices.emplace_back(top_right.x);
	square.vertices.emplace_back(top_right.y);
	square.vertices.emplace_back(top_right.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;

	square.vertices.emplace_back(top_right.x);
	square.vertices.emplace_back(top_right.y);
	square.vertices.emplace_back(top_right.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;

	square.vertices.emplace_back(top_left.x);
	square.vertices.emplace_back(top_left.y);
	square.vertices.emplace_back(top_left.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;

	square.vertices.emplace_back(bottom_left.x);
	square.vertices.emplace_back(bottom_left.y);
	square.vertices.emplace_back(bottom_left.z);
	square.vertices.emplace_back(input_color.Red);
	square.vertices.emplace_back(input_color.Green);
	square.vertices.emplace_back(input_color.Blue);
	square.vertices.emplace_back(input_color.Alpha);
	square.number_of_vertex_++;


	square.Initialize_VAO_VBO();



	square.bytes_of_data     = static_cast<unsigned int>(square.vertices.size()) * sizeof(float);
	square.primitive_        = GL_TRIANGLES;

	return square;
}



Mesh Mesh::Create_Circle(float size, int resolution, Color input_color)
{
	Mesh circle;

	auto i = 0;
	const auto angle = 360.0f / resolution * Math::inversed_radian;

	// Point in origin.
	circle.vertices.emplace_back(0.0f);
	circle.vertices.emplace_back(0.0f);
	circle.vertices.emplace_back(0.0f);
	circle.vertices.emplace_back(input_color.Red);
	circle.vertices.emplace_back(input_color.Green);
	circle.vertices.emplace_back(input_color.Blue);
	circle.vertices.emplace_back(input_color.Alpha);
	circle.number_of_vertex_++;

	while (i <= resolution)
	{
		const auto x = cosf(i * angle) * size;
		const auto y = sinf(i * angle) * size;

		const auto vector = vector3(x, y, 0.0f);



		circle.vertices.emplace_back(vector.x);
		circle.vertices.emplace_back(vector.y);
		circle.vertices.emplace_back(vector.z);
		circle.vertices.emplace_back(input_color.Red);
		circle.vertices.emplace_back(input_color.Green);
		circle.vertices.emplace_back(input_color.Blue);
		circle.vertices.emplace_back(input_color.Alpha);
		circle.number_of_vertex_++;
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

	auto x = cosf(angle) * size;
	auto y = sinf(angle) * size;
	const auto start = vector3(x, y, 0.0f);

	x = cos(angle + PI) * size;
	y = sin(angle + PI) * size;
	const auto end   = vector3(x, y, 0.0f);


	line.vertices.emplace_back(start.x);
	line.vertices.emplace_back(start.y);
	line.vertices.emplace_back(start.z);
	line.vertices.emplace_back(input_color.Red);
	line.vertices.emplace_back(input_color.Green);
	line.vertices.emplace_back(input_color.Blue);
	line.vertices.emplace_back(input_color.Alpha);
	line.number_of_vertex_++;

	line.vertices.emplace_back(end.x);
	line.vertices.emplace_back(end.y);
	line.vertices.emplace_back(end.z);
	line.vertices.emplace_back(input_color.Red);
	line.vertices.emplace_back(input_color.Green);
	line.vertices.emplace_back(input_color.Blue);
	line.vertices.emplace_back(input_color.Alpha);
	line.number_of_vertex_++;





	line.Initialize_VAO_VBO();


	line.bytes_of_data     = static_cast<unsigned int>(line.vertices.size()) * sizeof(float);
	line.primitive_        = GL_LINE_STRIP;

	return line;
}
*/
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