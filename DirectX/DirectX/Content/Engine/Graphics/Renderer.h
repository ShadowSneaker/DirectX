#pragma once
#include <map>
#include <string>

#include "../Math/DataTypes/Vertex.h"
#include "DirectXSetup.h"



struct SObjectCluster
{
	/// Properties

	// A reference to the mesh to be drawn.
	class CStaticMesh* Mesh{ nullptr };

	// A reference to the indexed shader to be used.
};


struct SShader
{
	/// Properties
	
	// A reference to the pixel shader.
	ID3D11PixelShader* PixelShader;

	// A reference to the vertex shader.
	ID3D11VertexShader* VertexShader;

	// A reference to the input layout.
	ID3D11InputLayout* InputLayout;
};


class CRenderer
{
	/// Properties

	CWindow* Window;
	CDirectXSetup* Setup;

	// A list of all the shaders loaded.
	std::map<std::string, SShader> Shaders;

	std::string WindowName{ "Name" };


	// TODO:
	// MOVE TO INPUT CLASS
	MSG Message{ 0 };
public:
	inline MSG GetMsg() const { return Message; }

public:
	/// Constructors.

	// Constructor, Default.
	CRenderer(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CRenderer();




	/// Functions

private:
	void DeleteShaders();


public:



	void DrawAll();
};