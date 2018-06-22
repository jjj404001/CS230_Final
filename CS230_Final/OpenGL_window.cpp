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
	PFD.iLayerType = PFD_MAIN_PLANE;



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

void OpenGL_window::SetGui()
{
	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	RECT size;
	GetClientRect(hWnd, &size);
	io.DisplaySize = ImVec2(static_cast<float>(size.right), static_cast<float>(size.bottom));
	io.DisplayFramebufferScale = ImVec2(size.right > 0 ? ((float)size.right / size.right) : 0, size.bottom > 0 ? ((float)size.bottom / size.bottom) : 0);

	// Setup time step
	//double current_time = glfwGetTime();
	//io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
	//g_Time = current_time;


	// Set OS mouse position if requested (only used when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
	if (io.WantSetMousePos)
	{
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}
	else
	{
		// 15 is cursor size.
		const auto mouse_x = RAWMousePos.x;
		const auto mouse_y = RAWMousePos.y;


		io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);
	}
	/*else
	{
		io.MousePos = ImVec2(-FLT_MAX, -FLT_MAX);
	}*/

	if(io.WantCaptureKeyboard)
	{
		io.KeyMap[ImGuiKey_A] = VK_A;
	}

	for (int i = 0; i < 3; i++)
	{
		// If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
		io.MouseDown[i] = MouseButton[i];
	}


}

MSG& OpenGL_window::GetGLMessage()
{
	return Message;
}
HDC* OpenGL_window::GetDeviceContext()
{
	return &device_context;
}

void OpenGL_window::ResizeOpenGLViewport(HWND /*hwnd*/)
{
	if (hWnd == nullptr)
		return;

	RECT rRect;

	// Extend
	GetClientRect(hWnd, &rRect);

	graphic.SetRect(rRect);
	glViewport(-1, -1, rRect.right, rRect.bottom); // Set viewport
	glOrtho(0, 0, rRect.right, rRect.top, 1, -1);
	glMatrixMode(GL_PROJECTION);
}

void OpenGL_window::ResizeCamera(short delta)
{
	graphic.camera.ResizeCamera(delta);
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
			if (camera_mode)
				HandleCameraTransform(wParam);
			else
				HandleTransform(wParam);
			break;
		case VK_P:
			graphic.TakeScreenShot();
			break;
		case VK_TAB:
			if(graphic.GetPolyMode() == GL_FILL)
				graphic.SetPolyMode(GL_LINE);
			else if (graphic.GetPolyMode() == GL_LINE)
				graphic.SetPolyMode(GL_POINT);
			else if (graphic.GetPolyMode() == GL_POINT)
				graphic.SetPolyMode(GL_FILL);
			break;
		case VK_C:
				camera_mode = !camera_mode;
			break;
		case VK_V:
				vsync_on = !vsync_on;
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

	RAWMousePos = result;

	MousePos = result;
	MousePos.x -= screen_x /2;

	MousePos.y = -MousePos.y;
	MousePos.y += screen_y / 2;


}

void OpenGL_window::Input_MouseButton()
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/ms646301(v=vs.85).aspx
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		MouseButton[0] = true;
	else if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		MouseButton[1] = true;
	else if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
		MouseButton[2] = true;
}

void OpenGL_window::Input_MouseButtonReleased()
{
	if ((GetKeyState(VK_LBUTTON) & 0x100) == 0)
		MouseButton[0] = false;
	else if ((GetKeyState(VK_LBUTTON) & 0x100) == 0)
		MouseButton[1] = false;
	else if ((GetKeyState(VK_LBUTTON) & 0x100) == 0)
		MouseButton[2] = false;
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
		if (selected_object_index == graphic.GetObjectList().size() - 1)
		{
			obj = &(graphic.GetObjectList()[0]);
			selected_object_index = 0;
		}
		else
			obj = &(graphic.GetObjectList()[selected_object_index += 1]);
	}

	
	//obj->shader = graphic.shader_program_POS_TEX;

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

void OpenGL_window::HandleCameraTransform(WPARAM wParam)
{
	auto input_vector = vector2();


	// Check input and set vector for transform.
	// Use if statement for diagonal functionality.
	if (wParam == VK_UP)
		input_vector.y += TRANSFORM_FACTOR;
	if (wParam == VK_DOWN)
		input_vector.y -= TRANSFORM_FACTOR;
	if (wParam == VK_LEFT)
		input_vector.x -= TRANSFORM_FACTOR;
	if (wParam == VK_RIGHT)
		input_vector.x += TRANSFORM_FACTOR;



	if (edit_mode_ == Translation)
		graphic.camera.MoveCamera(input_vector);
	else if (edit_mode_ == Rotation) // ONLY WORKS WITH HORIZONTAL ARROW.
		graphic.camera.RotateCamera(input_vector);
}

void OpenGL_window::Update()
{
	timer.Clock_Start();

	if (vsync_on)
		wglSwapIntervalEXT(1);
	else
		wglSwapIntervalEXT(0);

	




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
	UpdateGui();
	SwapBuffers(*GetDeviceContext());


	const auto duration = timer.Clock_End();

	ellapsed_time += duration;
	fps++;

	const std::string name = CLASS_NAME + std::to_string(previous_fps);
	const std::string name_additional = " Ellapsed time between frame : " + std::to_string(previous_ellapsed_time);

	const std::string mouse_pos_string = "  Mouse Position : (" + std::to_string(MousePos.x) + "," + std::to_string(-MousePos.y) + ")";

	SetWindowText(hWnd, (name + name_additional + mouse_pos_string).c_str());
	
	if (ellapsed_time > 1.0)
	{
		std::cout << "FPS  : " << fps << std::endl;
		std::cout << "TIME : " << ellapsed_time << std::endl;

		previous_fps = fps;
		previous_ellapsed_time = ellapsed_time;

		fps = 0;
		ellapsed_time = 0.0;
	}
}

void OpenGL_window::UpdateGui()
{
	if (selected_object.empty())
		return;


	ImGui::GetIO().WantCaptureMouse    = true;
	ImGui::GetIO().WantCaptureKeyboard = true;
	
	ImGui_ImplOpenGL3_NewFrame();
	SetGui();
	ImGui::NewFrame();
	{
		float translation[2] = { selected_object.back()->transform_.GetTranslation().x, selected_object.back()->transform_.GetTranslation().y };
		float rotation = selected_object.back()->transform_.GetRotation();
		float scale[2] = { selected_object.back()->transform_.GetScale().x, selected_object.back()->transform_.GetScale().y };
		

		ImGui::Text(selected_object.back()->name.c_str()); 
		ImGui::SliderFloat2("Translation", &translation[0], -500, 500); 
		ImGui::SliderAngle("Angle", &rotation, 0.0f, 360.0f);  
		ImGui::SliderFloat2("Scale", &scale[0], 0.0f, 2.0f);

		selected_object.back()->transform_.SetTranslation(vector2(translation[0], translation[1]));
		selected_object.back()->transform_.SetRotation(rotation);
		selected_object.back()->transform_.SetScale(vector2(scale[0], scale[1]));





		if (ImGui::Button("Select next object")) 
			SelectNextObject();

		if (ImGui::Button("Texture"))
		{
			selected_object.back()->shader = graphic.shader_program_POS_TEX;
		}

		if (ImGui::Button("Plain color"))
		{
			selected_object.back()->shader = graphic.shader_program_POS_COLOR;
		}
	}


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
