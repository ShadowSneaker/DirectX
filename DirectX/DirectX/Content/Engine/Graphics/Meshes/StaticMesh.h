#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <stdio.h>
#include <vector>

#include "../../Math/DataTypes/Vertex.h"


class CLoadMesh
{
private:
	/// Properties

	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;

	char* FBuffer;
	long FBufferSize;
	uint ActualSize;

	uint TokenPtr;

	ID3D11Buffer* VertexBuffer;

public:

	std::string FileName;

	std::vector<SVector> PositionList;
	std::vector<SVector> NormalList;
	std::vector<SVector2> TexCoordList;
	std::vector<int> PIndices;
	std::vector<int> TIndices;
	std::vector<int> NIndices;

	SVertex* Vertices;
	uint VertexCount;


public:
	/// Constructors
	CLoadMesh(char* File, ID3D11Device* InDevice, ID3D11DeviceContext* InDeviceContext);

	~CLoadMesh();




	/// Functions

	// TODO: Remove this function. - this should be done in the renderer class.
	void Draw();

private:
	int LoadFile(char* FileLocation);

	void ParseFile();
	bool GetNextLine();
	bool GetNextToken(int& TokenStart, int& TokenLength);

	bool CreateVB();
};



class CStaticMesh
{
private:
	/// Properties

	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;

	CLoadMesh* Object;
	ID3D11VertexShader* VShader;
	ID3D11PixelShader* PShader;
	ID3D11InputLayout* InputLayout;
	ID3D11Buffer* ConstantBuffer;

	SVector Location{ 0.0f };
	SVector Rotation{ 0.0f };
	float Scale{ 1.0f };


public:
	/// Constructors

	CStaticMesh(ID3D11Device* InDevice, ID3D11DeviceContext* DeviceContext);
};