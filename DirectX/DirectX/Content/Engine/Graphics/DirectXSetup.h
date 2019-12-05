#pragma once
#include "Window.h"


class CDirectXSetup
{
	D3D_DRIVER_TYPE DriverType{ D3D_DRIVER_TYPE_NULL };
	
	D3D_FEATURE_LEVEL FeatureLevel{ D3D_FEATURE_LEVEL_11_0 };


	ID3D11Device* Device{ NULL };
	
	ID3D11DeviceContext* DeviceContext{ NULL };

	IDXGISwapChain* SwapChain{ NULL };

	ID3D11RenderTargetView* BackBuffer{ NULL };

	ID3D11DepthStencilView* ZBuffer;


	CWindow* Window;

	float ClearColour[4] = { 0.3f, 0.3f, 0.3f, 1.0f };


public:
	/// Constructors

	// Constructor, Default.
	CDirectXSetup(CWindow* InWindow);

	// Destructor.
	~CDirectXSetup();


	/// Functions

	// Initalises all of DirectX's core setup.
	HRESULT Initialise();

	void ClearView();


	/// Getters

	INLINE ID3D11Device* GetDevice() const { return Device; }

	INLINE ID3D11DeviceContext* GetDeviceContext() const { return DeviceContext; }

	INLINE IDXGISwapChain* GetSwapChain() const { return SwapChain; }
};