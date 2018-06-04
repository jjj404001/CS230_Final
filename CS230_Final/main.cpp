#include "OpenGL_window.h"



#define FAKE true
#define NOT_FAKE false


OpenGL_window main_opengl;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpszCmdParam*/, int nCmdShow)
{
#ifdef _DEBUG
	AllocConsole();	//Allocate console
	FILE *OutStream;
	FILE *InStream;
	freopen_s(&OutStream, "CONOUT$", "wt", stdout);
	freopen_s(&InStream, "CONIN$", "r", stdin);
#endif



	OpenGL_window fake_window;


	main_opengl.Register_OpenGL_Class(hInstance, NOT_FAKE);

	fake_window.Register_OpenGL_Class(hInstance, FAKE);
	fake_window.Create_Old_Context(hInstance);


	

	// Set attrib
	Attributes attributes(main_opengl.major_version, main_opengl.minor_version);


	// Initialize glew
	glewInit();


	main_opengl.Create_Context(hInstance, attributes, fake_window, nCmdShow);






	SetActiveWindow(main_opengl.GetHWND());


	
	main_opengl.GetGraphicHandle().Initialize();
	while (!main_opengl.quit)
	{
		main_opengl.Update();
	}


	return static_cast<int>((main_opengl.GetGLMessage()).wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (msg) 
	{
		case WM_PAINT:
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		case WM_CLOSE:
			std::cout << "WM_CLOSE" << std::endl;
#ifdef _DEBUG
			FreeConsole();     //Destroy console.
#endif
			PostQuitMessage(0);
			main_opengl.quit = true;
			return 0;
		case WM_SIZE:
			main_opengl.ResizeOpenGLViewport(hWnd);
			break;
		case WM_KEYDOWN://if keyboard key is pressed.
		{
			// check if fullscreen 
			//auto wndStyle = GetWindowLong(hWnd, GWL_STYLE);
			main_opengl.Input_KeyDown(hWnd, wParam, lParam);
		}
		break;
		case WM_KEYUP: //if keyboard key is released.
		{

		}
		break;
		case WM_LBUTTONDOWN: //if left mouse button
		case WM_MBUTTONDOWN: //or middle mouse button
		case WM_RBUTTONDOWN: //or right mouse button is pressed.
		{
			std::cout << "Mouse" << std::endl;
		}
		break;
		case WM_LBUTTONUP: ///if left mouse button
		case WM_MBUTTONUP: //or middle mouse button
		case WM_RBUTTONUP: //or right mouse button is released.
		{

		}
		break;
		case WM_MOUSEWHEEL: //if mouse wheel is rolled.
		{

		}
		break;
		case WM_MOUSEMOVE: //if mouse is moved.
		{
			main_opengl.Input_MouseMove(hWnd, lParam);
		}
		break;
		case WM_DESTROY: //if mouse is moved.
		{
		}
		break;
	default: 
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}