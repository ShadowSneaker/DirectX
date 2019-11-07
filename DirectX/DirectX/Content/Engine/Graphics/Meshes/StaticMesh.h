#pragma once
#include "../../Math/DataTypes/Vertex.h"
#include "../../Math/DataTypes/Transform.h"
#include "../../Core/Systems/FileManager.h"

#include "../../Core/DataTypes/Colour.h"

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


typedef ID3D11ShaderResourceView STexture;


class CStaticMesh
{
private:
	/// Properties

	// The name and file path of this mesh.
	SFilePath FileName{ "" };


	// TEMP
	uint TokenPtr{ 0 };
	std::vector<SVector> PositionList{ std::vector<SVector>{} };
	std::vector<SVector> NormalList{ std::vector<SVector>{} };
	std::vector<SVector2> TexCoordList{ std::vector<SVector2>{} };
	std::vector<int> PIndices{ std::vector<int>{} };
	std::vector<int> TIndices{ std::vector<int>{} };
	std::vector<int> NIndices{ std::vector<int>{} };


protected:

	// A reference to all the vertices that is on this mesh.
	SVertex* Vertices{ nullptr };

	// The total amount of vertices that this mesh has.
	uint VertexCount{ 0 };

	// The shader type that this mesh uses.
	SShader Shader;

	// The applied texture on this mesh.
	STexture* Texture{ NULL };

public:
	// The location, rotation and scale of this mesh.
	STransform Transform;

	// Should the mesh's faces be looking inwards (false for outwards (default)).
	bool InvertFaces{ false };

	bool Reflect{ false };



public:
	/// Constructors

	// Constructor, Default.
	CStaticMesh();

	// Destructor.
	virtual ~CStaticMesh();


	/// Functions

private:
	// Applies all the vertices found in a file and sets them to this mesh.
	// @param FileInfo - The file information that was gathered when reading the .obj file.
	void SetupVertices(SFileInfo FileInfo);

	// 
	bool GetNextToken(SFileInfo File, int& Start, int& Length);

	// 
	bool GetNextLine(SFileInfo File);


public:


	/// Setters

	
	// Sets this mesh to a .obj mesh stored in files.
	// @param FilePath - The location of the file.
	// @param UseDefaultPath - Should the starting position for the search start in the default location for mesh files.
	void SetMesh(String FilePath, bool UseDefaultPath = true);

	// Sets the colour of this mesh.
	// @note - This multiplies the colour onto the object.
	// @param Red - The red component.
	// @param Green - The green component.
	// @param Blue - The blue component.
	// @param Alpha - The alpha of the colour.
	void SetColour(float Red, float Green, float Blue, float Alpha);

	// Sets the colour of this mesh.
	// @note - This multiplies the colour onto the object.
	// @param Colour - The colour values to set this mesh to.
	void SetColour(SColour Colour);


	/// Getters

	inline uint GetVertexCount() const { return VertexCount; }

	//inline SModelVertex* GetVertices() const { return Vertices; }
	inline SVertex* GetVertices() const { return Vertices; }

	SShader GetShader() const;

	ID3D11ShaderResourceView* GetTexture() { return Texture; }
};