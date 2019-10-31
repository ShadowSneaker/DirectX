#pragma once
#include "../../Math/DataTypes/Vertex.h"

#include <D3D11.h>
#include <DXGI.h>
#include <D3DX11.h>
#include <DxErr.h>
#include <Windows.h>


struct SShader
{
	/// Properties

	// A reference to the vertex buffer.
	ID3D11Buffer* ConstantBuffer;

	// A reference to the pixel shader.
	ID3D11PixelShader* PixelShader;

	// A reference to the vertex shader.
	ID3D11VertexShader* VertexShader;

	// A reference to the input layout.
	ID3D11InputLayout* InputLayout;


	void Clear()
	{
		if (ConstantBuffer) ConstantBuffer->Release();
		if (InputLayout) InputLayout->Release();
		if (VertexShader) VertexShader->Release();
		if (PixelShader) PixelShader->Release();
	}
};


class CStaticMesh
{
private:
	/// Properties
	class CRenderer* Renderer;

protected:

	//SModelVertex* Vertices;
	SVertexBase* Vertices;

	uint VertexCount;

	SShader Shader;


public:
	/// Constructors

	// Constructor, Default.
	CStaticMesh(class CRenderer* InRenderer);

	// Destructor.
	~CStaticMesh();


	/// Setters

	void SetShader(std::string FilePath, bool UseDefaultPath = true);


	/// Getters

	inline uint GetVertexCount() const { return VertexCount; }

	//inline SModelVertex* GetVertices() const { return Vertices; }
	inline SVertexBase* GetVertices() const { return Vertices; }

	SShader GetShader() const;
};