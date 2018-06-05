#include "Mesh.h"
#include <cmath>
#define PI 3.14159265f


namespace Math
{
	float inversed_radian = (PI) / 180;
}
//TODO: Apply ndc
Mesh Mesh::Create_Triangle(float size)
{
	Mesh tri;

	const auto bottom_left  = vector3(-size, -size, 0.0f);
	const auto bottom_right = vector3(size, -size, 0.0f);
	const auto top_middle   = vector3(0.0f,   size, 0.0f);



	tri.vertices.emplace_back(bottom_left);
	tri.vertices.emplace_back(bottom_right);
	tri.vertices.emplace_back(top_middle);



	tri.Initialize_VAO_VBO();




	tri.bytse_of_data     = static_cast<unsigned int>(tri.vertices.size()) * sizeof(vector3);
	tri.number_of_vertex_ = static_cast<unsigned int>(tri.vertices.size());
	tri.primitive_        = GL_TRIANGLES;

	return tri;
}

//TODO : fix below with vertex.

Mesh Mesh::Create_Square(float size)
{
	Mesh square;
	const auto bottom_left  = vector3(-size, -size, 0.0f);
	const auto bottom_right = vector3(size, -size, 0.0f);
	const auto top_right    = vector3(size, size, 0.0f);
	const auto top_left     = vector3(-size, size, 0.0f);

	square.vertices.emplace_back(bottom_left);
	square.vertices.emplace_back(bottom_right);
	square.vertices.emplace_back(top_right);
	square.vertices.emplace_back(top_right);
	square.vertices.emplace_back(top_left);
	square.vertices.emplace_back(bottom_left);





	square.Initialize_VAO_VBO();



	square.bytse_of_data     = static_cast<unsigned int>(square.vertices.size()) * sizeof(vector3);
	square.number_of_vertex_ = static_cast<unsigned int>(square.vertices.size());
	square.primitive_        = GL_TRIANGLES;

	return square;
}



Mesh Mesh::Create_Circle(float size, int resolution)
{
	Mesh circle;
	auto i = 0;
	const auto angle = 360.0f / resolution * Math::inversed_radian;

	// Point in origin.
	circle.vertices.emplace_back(0.0f, 0.0f, 0.0f);

	while (i <= resolution)
	{
		const auto x = cosf(i * angle) * size;
		const auto y = sinf(i * angle) * size;

		const auto vector = vector3(x, y, 0.0f);



		circle.vertices.emplace_back(vector);
		i++;
	}




	circle.Initialize_VAO_VBO();


	circle.bytse_of_data     = static_cast<unsigned int>(circle.vertices.size()) * sizeof(vector3);
	circle.number_of_vertex_ = static_cast<unsigned int>(circle.vertices.size());
	circle.primitive_ = GL_TRIANGLE_FAN;

	return circle;
}

Mesh Mesh::Create_Line(float size, float angle)
{
	Mesh line;


	auto x = cosf(angle) * size;
	auto y = sinf(angle) * size;
	const auto start = vector3(x, y, 0.0f);

	x = cos(angle + PI) * size;
	y = sin(angle + PI) * size;
	const auto end   = vector3(x, y, 0.0f);


	line.vertices.emplace_back(start);
	line.vertices.emplace_back(end);






	line.Initialize_VAO_VBO();


	line.bytse_of_data     = static_cast<unsigned int>(line.vertices.size()) * sizeof(vector3);
	line.number_of_vertex_ = static_cast<unsigned int>(line.vertices.size());
	line.primitive_        = GL_LINE_STRIP;

	return line;
}

void Mesh::Initialize_VAO_VBO()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &VBO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bytse_of_data, &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
}

void Mesh::Update_VAO_VBO()
{
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bytse_of_data, &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
}