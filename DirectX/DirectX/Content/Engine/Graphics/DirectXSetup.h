#pragma once
#include "Window.h"


class CDirectXSetup
{
	D3D_DRIVER_TYPE DriverType{ D3D_DRIVER_TYPE_NULL };
	D3D_FEATURE_LEVEL FeatureLevel{ D3D_FEATURE_LEVEL_11_0 };


	ID3D11Device* Device{ NULL };
	ID3D11DeviceContext* DeviceContext{ NULL };

	IDXGISwapChain* SwapChain{ NULL };

	CWindow* Window;


public:
	/// Constructors

	// Constructor, Default.
	CDirectXSetup(CWindow* InWindow);

	// Destructor.
	~CDirectXSetup();


	/// Functions

	// Initalises all of DirectX's core setup.
	HRESULT Initialise();
};