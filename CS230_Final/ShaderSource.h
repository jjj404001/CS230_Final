#pragma once

#define VERT_SOURCE_COLOR_INPUT R"(
#version 330 core
layout (location = 0) in vec3 attribute_Pos;  // Attribute at 0 is position.
layout (location = 1) in vec3 attribute_Color;// Attribute at 1 is color.

out vec3 vert_shader_out;

uniform mat3 combined;
uniform vec3 colorinput;


void main()
{
	vec3 position = combined * vec3(attribute_Pos.xy, 1.0f);
    gl_Position = vec4(position.xy, 0.0, 1.0);
	vert_shader_out = colorinput;
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
layout (location = 0) in vec3 attribute_Pos;
layout (location = 1) in vec3 attribute_Color;
layout (location = 2) in vec2 attribute_Texture;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat3 combined;


void main()
{
	vec3 position = combined * vec3(attribute_Pos.xy, 1.0f);
    gl_Position = vec4(position.xy, 0.0, 1.0);
    ourColor = attribute_Color;
    TexCoord = attribute_Texture;
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
layout (location = 0) in vec3 attribute_Pos;
layout (location = 1) in vec3 BufferColor;
layout (location = 2) in vec2 BufferTexCord;

out vec3 Color;
out vec2 TexCord;


uniform mat3 combined;


void main()
{
   vec3 position = combined * vec3(attribute_Pos.xy, 1.0f);
    gl_Position = vec4(position.xy, 0.0, 1.0);
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