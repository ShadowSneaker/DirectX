#pragma once
#include "Window.h"


// Used to initalise the core components of DirectX.
class CDirectXSetup
{
	// The driver type used.
	D3D_DRIVER_TYPE DriverType{ D3D_DRIVER_TYPE_NULL };
	
	// The feature level used.
	D3D_FEATURE_LEVEL FeatureLevel{ D3D_FEATURE_LEVEL_11_0 };

	// The created Direct3D device.
	ID3D11Device* Device{ NULL };
	
	// The created Direct3D device context.
	ID3D11DeviceContext* DeviceContext{ NULL };

	// The created Direct3D swap chain.
	IDXGISwapChain* SwapChain{ NULL };

	// The created back buffer.
	ID3D11RenderTargetView* BackBuffer{ NULL };

	// The created ZBuffer.
	ID3D11DepthStencilView* ZBuffer;

	// A reference to the created window.
	CWindow* Window;

	// The colour the window should be cleared in.
	// @default - Gray (0.3f, 0.3f, 0.3f, 1.0f).
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

	// Clears the window view.
	void ClearView();



	/// Getters

	// Returns a reference to the Direct3D Device.
	INLINE ID3D11Device* GetDevice() const { return Device; }

	// Returns a reference to the Direct3D Device Context.
	INLINE ID3D11DeviceContext* GetDeviceContext() const { return DeviceContext; }

	// Returns a reference to the swap chain.
	INLINE IDXGISwapChain* GetSwapChain() const { return SwapChain; }
};