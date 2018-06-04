#pragma once
#include <string>
#include "Object.h"

class Graphics
{
	unsigned int vertex_shader;
	const char*  vertex_shader_source = VERT_SOURCE;

	unsigned int fragment_shader;
	const char*  fragment_shader_source = FRAG_SOURCE;

	unsigned int shader_program;

	unsigned int polygon_mod = GL_FILL;

	std::vector<Object> objects_list;
	unsigned int current_index_of_mesh = 0;

	RECT rect_;

	void SetUpShader(const char* input_vertext_source, const char*  input_fragment_source);
public:
	void Initialize();
	void Update();

	void SetRect(RECT input_rect) { rect_ = input_rect; }

	unsigned int GetPolyMode() { return polygon_mod; }
	void SetPolyMode(unsigned int input) { polygon_mod = input; }


	void AddObject(Object input_object);

	void MoveEverything();
	void ScaleEverything();
	void RotateEverything();
};