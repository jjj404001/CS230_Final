#include "OpenGL_window.h"
#include "resource.h"
#include <winuser.h>
#include "VirtualKeyCodes.h"


#define GREEN 0.0f, 0.586f, 0.0f, 1.0f
// Prototype
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


void OpenGL_window::Register_OpenGL_Class(HINSTANCE hInstance, bool is_fake)
{
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	if (is_fake)
		WndClass.lpfnWndProc = DefWindowProc;
	else
		WndClass.lpfnWndProc = static_cast<WNDPROC>(WndProc);
	WndClass.lpszClassName = CLASS_NAME;
	WndClass.lpszMenuName = nullptr;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;



	RegisterClass(&WndClass);
}

bool OpenGL_window::Create_Old_Context(HINSTANCE hInstance)
{
	hWnd = CreateWindow(CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, static_cast<HMENU>(nullptr), hInstance, nullptr);

	device_context = GetDC(hWnd);        // Device Context



	ZeroMemory(&PFD, sizeof(PFD));
	PFD.nSize = sizeof(PFD);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 32;
	PFD.cAlphaBits = 8;
	PFD.cDepthBits = 24;



	//fake_window.PFDID = ChoosePixelFormat(fake_window.device_context, &fake_window.PFD);
	//if (!fake_window.PFDID)
	//	return 1;

	//if (!SetPixelFormat(fake_window.device_context, fake_window.PFDID, &fake_window.PFD))
	//	return 1;

	PixelFormat = ChoosePixelFormat(device_context, &PFD);
	if (!PixelFormat)
		return false;

	if (!SetPixelFormat(device_context, PixelFormat, &PFD))
		return false;



	rendering_context = wglCreateContext(device_context);
	wglMakeCurrent(device_context, rendering_context);

	return true;
}

bool OpenGL_window::Destroy_Old_Context()
{
	wglMakeCurrent(nullptr, nullptr);
	wglDeleteContext(rendering_context);
	ReleaseDC(hWnd, device_context);
	DestroyWindow(hWnd);



	return true;
}

bool OpenGL_window::Create_Context(const HINSTANCE hInstance, const Attributes input_attrib, OpenGL_window& fake, const int nCmdShow)
{
	hWnd = CreateWindow(CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
						0, 0, WINDOW_SIZE, WINDOW_SIZE,
						NULL, static_cast<HMENU>(nullptr), hInstance, nullptr);

	device_context = GetDC(hWnd);





	const bool status = wglChoosePixelFormatARB(device_context, input_attrib.pixelAttribs, NULL, 1, &fake.pixelFormatID, &fake.numFormats);

	if (!status || fake.numFormats == 0)
		return true;



	DescribePixelFormat(device_context, fake.pixelFormatID, sizeof(PFD), &PFD);
	SetPixelFormat(device_context, fake.pixelFormatID, &PFD);




	rendering_context = wglCreateContextAttribsARB(device_context, 0, input_attrib.contextAttribs);
	if (rendering_context == nullptr)
		return 1;


	fake.Destroy_Old_Context();

	if (!wglMakeCurrent(device_context, rendering_context))
		return false;


	ShowWindow(hWnd, nCmdShow);
	


	return true;
}
MSG& OpenGL_window::GetGLMessage()
{
	return Message;
}
HDC* OpenGL_window::GetDeviceContext()
{
	return &device_context;
}

void OpenGL_window::ResizeOpenGLViewport()
{
	if (hWnd == nullptr)
		return;

	RECT rRect;

	// Extend
	GetClientRect(hWnd, &rRect);
	glViewport(-1, -1, rRect.right, rRect.bottom); // Set viewport
	glOrtho(rRect.left, rRect.right, rRect.bottom, rRect.top, 1.0f, -1.0f);
	glMatrixMode(GL_PROJECTION);

	// Set rect for ndc.
	graphic.SetRect(rRect);
}

void OpenGL_window::Input_KeyDown(WPARAM wParam, LPARAM lParam)
{
	WINDOWINFO test;
	test.cbSize = sizeof(WINDOWINFO);
	GetWindowInfo(hWnd, &test);

	switch (wParam)
	{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_CLOSE, wParam, lParam);
			break;
		case VK_RETURN:
			Check_and_Set_Fullscreen();
			break;
		case VK_G:
			edit_mode_ = Translation;
			/*if (selected_object.empty())
			{
				std::cout << "WARNING :: Nothing selected." << std::endl;
				break;
			}
			graphic.MoveSelected(*selected_object.back());*/
			break;
		case VK_S:
			edit_mode_ = Scale;
			/*if (selected_object.empty())
			{
				std::cout << "WARNING :: Nothing selected." << std::endl;
				break;
			}
			graphic.ScaleSelected(*selected_object.back());*/
			break;
		case VK_R:
			edit_mode_ = Rotation;
			/*if (selected_object.empty())
			{
				std::cout << "WARNING :: Nothing selected." << std::endl;
				break;
			}
			graphic.RotateSelected(*selected_object.back());*/
			break;
		case VK_SPACE:
			SelectNextObject();
			break;
		case VK_UP:
		case VK_DOWN:
		case VK_LEFT:
		case VK_RIGHT:
			HandleTransform(wParam);
			break;
		default: ;
	}
}

void OpenGL_window::Input_MouseMove(LPARAM lParam)
{
	const auto result = MAKEPOINTS(lParam);
	RECT rect;
	GetWindowRect(hWnd, &rect);

	const auto screen_x = static_cast<SHORT>(rect.right);
	const auto screen_y = static_cast<SHORT>(rect.bottom);

	MousePos = result;
	MousePos.x -= screen_x /2;

	MousePos.y = -MousePos.y;
	MousePos.y += screen_y / 2;
}


void OpenGL_window::Check_and_Set_Fullscreen()
{
	if (!is_fullscreen) // fullscreen
	{
		std::cout << "Fullscreen" << std::endl;
		SetWindowLong(hWnd, GWL_STYLE, NULL);
		ShowWindow(hWnd, SW_MAXIMIZE);

		is_fullscreen = true;
	}
	else
	{
		std::cout << "Not fullscreen" << std::endl;
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, nullptr, 0, 0, WINDOW_SIZE, WINDOW_SIZE, 0);
		ShowWindow(hWnd, SW_RESTORE);

		is_fullscreen = false;
	}
}



void OpenGL_window::SelectNextObject()
{
	Object* obj = nullptr;

	// if nothing selected, select first object in the list.
	if(selected_object.empty())
		obj = &(graphic.GetObjectList()[selected_object_index]);
	else
	{
		for (auto current_object : selected_object)
			current_object->shader = graphic.shader_program_POS_COLOR;

		if (selected_object_index == graphic.GetObjectList().size() - 1)
		{
			obj = &(graphic.GetObjectList()[0]);
			selected_object_index = 0;
		}
		else
			obj = &(graphic.GetObjectList()[selected_object_index += 1]);
	}

	
	obj->shader = graphic.shader_program_POS_COLOR;

	selected_object.clear();
	selected_object.push_back(obj);
}

void OpenGL_window::HandleTransform(WPARAM wParam)
{
	auto input_vector = vector2();


	// Check input and set vector for transform.
	// Use if statement for diagonal functionality.
	if(wParam == VK_UP)
		input_vector.y += TRANSFORM_FACTOR;
	if(wParam == VK_DOWN)
		input_vector.y -= TRANSFORM_FACTOR;
	if(wParam == VK_LEFT)
		input_vector.x -= TRANSFORM_FACTOR;
	if(wParam == VK_RIGHT)
		input_vector.x += TRANSFORM_FACTOR;


	if (selected_object.empty())
	{
		std::cout << "!!WARNING!! No object selected" << std::endl;
		return;
	}
	
	// Check current edit mode and transform.
	auto current_object = selected_object.back();
	if(edit_mode_ == Translation)
		graphic.MoveSelected(current_object, input_vector);
	else if (edit_mode_ == Scale)
		graphic.ScaleSelected(current_object, input_vector);
	else if (edit_mode_ == Rotation) // ONLY WORKS WITH HORIZONTAL ARROW.
		graphic.RotateSelected(current_object, input_vector);
}

void OpenGL_window::Update()
{
	timer.Clock_Start();

	if (fps >= 60)
		Sleep(static_cast<DWORD>(timer.GetDuration().count())); // For lab
		//Sleep(static_cast<DWORD>(1000 - timer.GetDuration().count())); // For home
	// Sleep for 1second - ellapsed time. so we can rest remaining of second.

	




	if (PeekMessage(&GetGLMessage(), nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&GetGLMessage());
		DispatchMessage(&GetGLMessage());
	}



	

	//graphic.SetPolyMode(GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, graphic.GetPolyMode());



	glClearColor(GREEN);
	glClear(GL_COLOR_BUFFER_BIT);
	graphic.Update();
	SwapBuffers(*GetDeviceContext());


	const auto duration = timer.Clock_End();

	ellapsed_time += duration;
	fps++;

	if (ellapsed_time > 1.0)
	{
		std::cout << "FPS  : " << fps << std::endl;
		std::cout << "TIME : " << ellapsed_time << std::endl;

		fps = 0;
		ellapsed_time = 0.0;
	}
}
