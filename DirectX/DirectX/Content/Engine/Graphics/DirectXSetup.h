#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#include "../Math/DataTypes/Vertex.h"
#include "Camera.h"


#include "../Font/Font.h"


struct SConstantBuffer
{
	SMatrix4 WorldProjection;
	float RedAmount{ 0.0f };
	float Scale;
	SVector2 Packing;
};


class CDirectXSetup
{
private:
	/// Properties
	
	HINSTANCE Instance{ NULL };

	HWND WindowHandle{ NULL };

	D3D_DRIVER_TYPE DriverType{ D3D_DRIVER_TYPE_NULL };

	D3D_FEATURE_LEVEL FeatureLevel{ D3D_FEATURE_LEVEL_11_0 };

	ID3D11Device* Device{ NULL };
	ID3D11DeviceContext* DeviceContext{ NULL };
	IDXGISwapChain* SwapChain{ NULL };

	char ProjectName[100] = "Game Project";

	MSG Message{ 0 };

	ID3D11Buffer* VertexBuffer;

	ID3D11VertexShader* VertexShader;

	ID3D11PixelShader* PixelShader;

	ID3D11InputLayout* InputLayout;

	ID3D11RenderTargetView* BackBufferRTView{ NULL };

	ID3D11Buffer* ConstantBuffer;

	ID3D11DepthStencilView* ZBuffer;

	ID3D11ShaderResourceView* Texture0;

	ID3D11SamplerState* Sampler0;



	CCamera* Camera;

	CFont* TempText;

	float TempRotate = 0.0f;

public:
	/// Constructors

	// Constructor, Default.
	CDirectXSetup();

	// Destructor.
	~CDirectXSetup();


	/// Functions

	// Setups and creates the window.
	// @param HandleInstance - 
	// @param CmdShow - 
	// @return - Returns true if the window was successfully created.
	bool Init(HINSTANCE HandleInstance, int CmdShow);

	void ReadMessage();

	HRESULT InitialiseWindow(HINSTANCE HandleInstance, int CmdShow);
	
	HRESULT InitialiseD3D();

	void ShutdownD3D();

	void RenderFrame();

	HRESULT InitialiseGraphics();


	/// TEMPORARY
	

	static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);


	/// Getters

	inline MSG GetMessage() const { return Message; }
};