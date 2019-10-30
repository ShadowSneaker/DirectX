#pragma once
#include "Window.h"

#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <Windows.h>

#include <string>

#include "../Math/DataTypes/Vector.h"


class CWindow
{
private:

	HINSTANCE HInstance{ NULL };

	HWND HWindow{ NULL };

	// The name that will be displayed at the top of the window.
	std::string ApplicationName{ "Name" };

	SVector2i WindowSize{ 640, 480 };



public:
	/// Constructors

	CWindow(std::string WindowName);


	/// Functions

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