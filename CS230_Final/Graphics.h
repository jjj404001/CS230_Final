#pragma once
#include <string>
#include "Object.h"
#include "ShaderSource.h"
#include "Font.h"
#include "Text.h"
#include "Camera.h"

class Graphics
{
	friend class OpenGL_window;
	Font font;
	Camera camera;

	unsigned int vertex_shader;
	const char*  vertex_shader_source;

	unsigned int fragment_shader;
	const char*  fragment_shader_source;

	

	unsigned int polygon_mod = GL_FILL;

	std::vector<Object> objects_list;
	std::vector<Text> text_list;
	unsigned int current_index_of_mesh = 0;

	//RECT rect_;
public:
	unsigned int shader_program_POS_BLACK;
	unsigned int shader_program_POS_RED;
	unsigned int shader_program_POS_COLOR;
	unsigned int shader_program_POS_TEX;
	unsigned int shader_program_FONT;


	void Initialize();
	void Update();

	void Objects_update();
	void Texts_update();

	void TakeScreenShot();

	//void SetRect(RECT input_rect) { rect_ = input_rect; }

	unsigned int GetPolyMode() { return polygon_mod; }
	void SetPolyMode(unsigned int input) { polygon_mod = input; }

	std::vector<Object>& GetObjectList() { return objects_list; }


	void AddObject(Object input_object, unsigned int input_shader);

	void SetUpShader(unsigned int& shader_program, const char* input_vertext_source, const char*  input_fragment_source);

	void MoveEverything();
	void ScaleEverything();
	void RotateEverything();

	void MoveSelected(Object* input_object, vector2 translation_input);
	void ScaleSelected(Object* input_object, vector2 translation_input);
	void RotateSelected(Object* input_object, vector2 translation_input);
};