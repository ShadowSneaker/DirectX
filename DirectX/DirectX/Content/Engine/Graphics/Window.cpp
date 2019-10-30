#include "Window.h"



// FIND A GOOD PLACE FOR THIS.
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


CWindow::CWindow(std::string WindowName)
	:ApplicationName{ WindowName }
{}


HRESULT CWindow::InitialiseWindow(HINSTANCE HandleInstance, int CommandShow)
{
	WNDCLASSEX WCex = { 0 };
	WCex.cbSize = sizeof(WNDCLASSEX);
	WCex.style = CS_HREDRAW | CS_VREDRAW;
	WCex.lpfnWndProc = WindowProc;
	WCex.hInstance = HandleInstance;
	WCex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//WCex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WCex.lpszClassName = ApplicationName.c_str();

	if (!RegisterClassEx(&WCex)) return E_FAIL;

	
	// Create Window
	HInstance = HandleInstance;
	RECT Rect;
	Rect.left = 0;
	Rect.top = 0;
	Rect.right = WindowSize[X];
	Rect.bottom = WindowSize[Y];

	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);
	HWindow = CreateWindow(ApplicationName.c_str(), ApplicationName.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Rect.right - Rect.left, Rect.bottom - Rect.top, NULL, NULL, HInstance, NULL);

	if (!HWindow) return E_FAIL;

	ShowWindow(HWindow, CommandShow);
	return S_OK;
}


LRESULT CALLBACK WindowProc(HWND HWindow, UINT Message, WPARAM WParam, LPARAM LParam)
{
	PAINTSTRUCT PS;
	HDC Hdc;

	switch (Message)
	{
	case WM_PAINT:
		Hdc = BeginPaint(HWindow, &PS);
		EndPaint(HWindow, &PS);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default:
		return DefWindowProc(HWindow, Message, WParam, LParam);
	}

	return 0;
}