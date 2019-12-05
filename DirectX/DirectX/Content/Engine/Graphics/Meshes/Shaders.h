#pragma once
#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <Windows.h>

struct SShader
{
	/// Properties

	ID3D11Buffer* VertexBuffer{ nullptr };

	// A reference to the vertex buffer.
	ID3D11Buffer* ConstantBuffer{ nullptr };

	// A reference to the pixel shader.
	ID3D11PixelShader* PixelShader{ nullptr };

	// A reference to the vertex shader.
	ID3D11VertexShader* VertexShader{ nullptr };

	// A reference to the input layout.
	ID3D11InputLayout* InputLayout{ nullptr };


	void Clear()
	{
		if (VertexBuffer) VertexBuffer->Release();
		if (ConstantBuffer) ConstantBuffer->Release();
		if (InputLayout) InputLayout->Release();
		if (VertexShader) VertexShader->Release();
		if (PixelShader) PixelShader->Release();
	}
};