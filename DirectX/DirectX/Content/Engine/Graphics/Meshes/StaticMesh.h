#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <dxerr.h>
#include <stdio.h>
#include <vector>

#include "../../Math/DataTypes/Vertex.h"
#include "../../Math/DataTypes/Matrix.h"


struct SModelBuffer
{
	SMatrix4 WorldMatrix;
};


class CLoadMesh
{
public:
	struct SMeshVertex
	{
		SVector Position;
		SVector2 UV;
		SVector3 Normal;
	};

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

	SMeshVertex* Vertices;
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

/*class ObjFileModel
{
private:
	ID3D11Device* pD3DDevice;
	ID3D11DeviceContext* pImmediateContext;



	//////////////////////////////////////////////////

	int loadfile(char* fname);

	char* fbuffer;
	long fbuffersize; // filesize
	size_t actualsize; // actual size of loaded data (can be less if loading as text files as ASCII CR (0d) are stripped out)

//////////////////////////////////////////////////

	void parsefile();
	bool getnextline();
	bool getnexttoken(int& tokenstart, int& tokenlength);

	unsigned int  tokenptr;

	//////////////////////////////////////////////////

	bool createVB();

	ID3D11Buffer* pVertexBuffer;

public:

	struct xyz { float x, y, z; };	//used for vertices and normals during file parse
	struct xy { float x, y; };		//used for texture coordinates during file parse

	// Define model vertex structure
	struct MODEL_POS_TEX_NORM_VERTEX
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 TexCoord;
		DirectX::XMFLOAT3 Normal;
	};


	std::string filename;

	ObjFileModel(char* filename, ID3D11Device* device, ID3D11DeviceContext* context);
	~ObjFileModel();

	void Draw(void);

	std::vector <xyz> position_list;		// list of parsed positions
	std::vector <xyz> normal_list;		// list of parsed normals
	std::vector <xy> texcoord_list;		// list of parsed texture coordinates
	std::vector <int> pindices, tindices, nindices; // lists of indicies into above lists derived from faces

	MODEL_POS_TEX_NORM_VERTEX* vertices;
	unsigned int numverts;
};*/








class CStaticMesh
{
private:
	/// Properties

	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;

	CLoadMesh* Object{ nullptr };
	//ObjFileModel* Object{ nullptr };
	ID3D11VertexShader* VShader{ nullptr };
	ID3D11PixelShader* PShader{ nullptr };
	ID3D11InputLayout* InputLayout{ nullptr };
	ID3D11Buffer* ConstantBuffer{ nullptr };


public:

	SVector Location{ 0.0f };
	SVector Rotation{ 0.0f };
	float Scale{ 1.0f };


public:
	/// Constructors

	CStaticMesh(ID3D11Device* InDevice, ID3D11DeviceContext* DeviceContext);
	~CStaticMesh();

	/// Functions

	HRESULT SetMesh(char* FileName);

	void Draw(SMatrix4* World, SMatrix4* Projection);
};