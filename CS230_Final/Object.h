#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"

class Camera;
class Object
{
	friend class OpenGL_window;
public:
	std::string name = "Object";
	Transform transform_;
	Mesh mesh_;
	Texture texture_;
	unsigned int shader;
	bool is_HUD = false;
	bool is_collide = false;

	std::vector<vector2> separation_axis;

	void Update(RECT input_rect, Camera input_camera);

	//std::vector<vector2>& GetEdges()  { return separation_axis; };

	Object();
	Object(Transform input_transform, Mesh input_mesh);
	Object(Transform input_transform, Mesh input_mesh, Texture input_texture);
};