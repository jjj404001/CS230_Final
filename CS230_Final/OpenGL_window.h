#pragma once
#include"Attributes.h"
#include "VirtualKeyCodes.h"
#include "Timer.h"
#include "Graphics.h"
#include <iostream>

#define CLASS_NAME "OpenGL_window.h man we a"
#define WINDOW_SIZE 1000

class OpenGL_window
{
	HWND hWnd;
	HDC device_context;
	HGLRC rendering_context;
	MSG Message;
	WNDCLASS WndClass;
	POINTS MousePos;

	PIXELFORMATDESCRIPTOR PFD;
	int pixelFormatID;
	UINT numFormats;

	Timer timer;
	Graphics graphic;
	

	unsigned int fps = 0;
	double ellapsed_time = 0.0;


	int PFDID = NULL;
	int PixelFormat = NULL;

	void Check_and_Set_Fullscreen(HWND hWnd);
public:
	int major_version = 3;
	int minor_version = 3;
	bool is_fullscreen = false;
	bool quit = false;

	





	void Update();

	void Register_OpenGL_Class(HINSTANCE hInstance, bool is_fake);
	bool Create_Old_Context(HINSTANCE hInstance);
	bool Destroy_Old_Context();
	bool Create_Context(HINSTANCE hInstance, Attributes input_attrib, OpenGL_window& fake, int nCmdShow);


	MSG& GetGLMessage();
	HDC* GetDeviceContext();
	HWND& GetHWND() { return hWnd; };
	void ResizeOpenGLViewport(HWND hWnd);
	void Input_KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void Input_MouseMove(HWND hWnd, LPARAM lParam);

	Graphics& GetGraphicHandle() { return graphic; };
};
