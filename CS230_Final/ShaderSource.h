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



#define VERT_SOURCE_TEXTURE_POS R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
)"

#define FRAG_SOURCE_TEXTURE_POS R"(
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}
)"



















#define VERT_SOURCE_COLOR_POS_FONT R"(
#version 330 core
layout (location = 0) in vec3 BufferPos;
layout (location = 1) in vec3 BufferColor;
layout (location = 2) in vec2 BufferTexCord;

out vec3 Color;
out vec2 TexCord;

void main()
{
    gl_Position = vec4(BufferPos, 1.0);
    Color = BufferColor;
    TexCord = BufferTexCord;
}
)"

#define FRAG_SOURCE_COLOR_POS_FONT R"(
#version 330 core
out vec4 FragColor;
  
in vec3 Color;
in vec2 TexCord;

uniform sampler2D Texture;

void main()
{
    vec4 temp = texture2D(Texture, TexCord);

	if(temp.r == 0.0 && temp.g == 0.0 && temp.b == 0.0)
		discard;
	else
		temp = vec4(Color , 1.0);

	FragColor = temp;
}
)"