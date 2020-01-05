#pragma once
#include "Window.h"

#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <Windows.h>

#include <string>

#include "../Math/DataTypes/Vector.h"



// A class used to create a window.
class CWindow
{
private:
	// The handle instance of the window.
	HINSTANCE HInstance{ NULL };

	// The Window Handle.
	HWND HWindow{ NULL };

	// The name that will be displayed at the top of the window.
	std::string ApplicationName{ "Name" };

	// The size of the window (in pixels).
	SVector2i WindowSize{ 1920, 1080 };



public:
	/// Constructors

	// Constructor, Default.
	CWindow(std::string WindowName);



	/// Functions

	// Creates the window object.
	HRESULT InitialiseWindow(HINSTANCE HandleInstance, int CommandShow);



	/// Getters

	// Returns the handle instance.
	inline HINSTANCE GetHandle() const { return HInstance; }

	// Returns the window handle.
	inline HWND GetWindowHandle() const { return HWindow; }

	// Retursn the name of the application.
	inline std::string GetName() const { return ApplicationName; }

	// Returns the size of the window.
	inline SVector2i GetWindowSize() const { return WindowSize; }
};