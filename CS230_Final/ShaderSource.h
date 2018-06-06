#pragma once


#define VERT_SOURCE_POSITION R"(
#version 330 core
layout(location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
							)"
#define FRAG_SOURCE_COLOR_RED R"(
								#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
} 
								)"

#define FRAG_SOURCE_COLOR_BLUE R"(
								#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
} 
								)"

#define FRAG_SOURCE_COLOR_BLACK R"(
#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
} 
								)"


#define VERT_SOURCE_COLOR_INPUT R"(
#version 330 core
layout (location = 0) in vec3 attribute_Pos;  // Attribute at 0 is position.
layout (location = 1) in vec3 attribute_Color;// Attribute at 1 is color.

out vec3 vert_shader_out;

void main()
{
	gl_Position = vec4(attribute_Pos, 1.0);
	vert_shader_out = attribute_Color;
} 
								)"


#define FRAG_SOURCE_COLOR_INPUT R"(
#version 330 core
out vec4 FragColor;
in vec3 vert_shader_out; // Get color data

void main()
{
	FragColor = vec4(vert_shader_out, 1.0);
} 
								)"