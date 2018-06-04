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