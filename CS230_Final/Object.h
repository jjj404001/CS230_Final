#pragma once
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"

class Camera;
class Object
{
public:
	Transform transform_;
	Mesh mesh_;
	Texture texture_;
	unsigned int shader;
	bool is_HUD = false;


	void Update(RECT input_rect, Camera input_camera);

	Object();
	Object(Transform input_transform, Mesh input_mesh);
	Object(Transform input_transform, Mesh input_mesh, Texture input_texture);
};