#pragma once
#include"Attributes.h"
#include "Timer.h"
#include "Graphics.h"
#include "Edit.h"
#include <list>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>

#define CLASS_NAME "JJJ's Final assignment FPS:"
#define WINDOW_SIZE 1000
#define TRANSFORM_FACTOR 1.0f // move for 10 pixel

class OpenGL_window
{
	HWND hWnd;
	HDC device_context;
	HGLRC rendering_context;
	MSG Message;
	WNDCLASS WndClass;
	POINTS MousePos;
	POINTS RAWMousePos;
	bool MouseButton[5];

	PIXELFORMATDESCRIPTOR PFD;
	int pixelFormatID;
	UINT numFormats;

	Timer timer;
	Graphics graphic;
	ImGuiIO io;
	EditMode edit_mode_ = Translation;
	

	unsigned int fps = 0;
	double ellapsed_time = 0.0;

	unsigned int previous_fps = 0;
	double previous_ellapsed_time = 0.0;

	bool vsync_on = true;
	bool camera_mode = false;


	int PFDID = NULL;
	int PixelFormat = NULL;

	void Check_and_Set_Fullscreen();
	void SetGui();

	std::list<Object*> selected_object;
	unsigned int selected_object_index = 0;
public:
	int major_version = 3;
	int minor_version = 3;
	bool is_fullscreen = false;
	bool quit = false;

	


	void SelectNextObject();
	void HandleTransform(WPARAM wParam);
	void HandleCameraTransform(WPARAM wParam);



	void Update();

	void Register_OpenGL_Class(HINSTANCE hInstance, bool is_fake);
	bool Create_Old_Context(HINSTANCE hInstance);
	bool Destroy_Old_Context();
	bool Create_Context(HINSTANCE hInstance, Attributes input_attrib, OpenGL_window& fake, int nCmdShow);

	

	MSG& GetGLMessage();
	HDC* GetDeviceContext();
	HGLRC* GetRenderingContext() { return &rendering_context; };
	HWND& GetHWND() { return hWnd; };
	ImGuiIO& GetImGuiIO() { return io; }
	void SetImGuiIO(ImGuiIO& input_io) { io = input_io; }
	void ResizeOpenGLViewport(HWND hWnd);
	void ResizeCamera(short delta);
	void Input_KeyDown(WPARAM wParam, LPARAM lParam);
	void Input_MouseMove(LPARAM lParam);
	void Input_MouseButton();
	void Input_MouseButtonReleased();

	Graphics& GetGraphicHandle() { return graphic; };
};
