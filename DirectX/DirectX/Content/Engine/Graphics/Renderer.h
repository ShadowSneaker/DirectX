#pragma once
#include <map>
#include <string>
#include <vector>

#include "../Math/DataTypes/Vertex.h"
#include "DirectXSetup.h"
#include "../Core/Systems/FileReader.h"
#include "Meshes/StaticMesh.h"
#include "../Math/DataTypes/Matrix.h"


struct CBuffer
{
	SMatrix4 ViewMatrix;
	float RedFactor;
	float Scale;
	SVector2 Packing;
};




class CRenderer
{
private:
	/// Properties

	const std::string DefaultFilePath{ "Content/Assets/Shaders/" };
	

	CWindow* Window;
	CDirectXSetup* Setup;

	// A list of all the shaders loaded.
	//std::map<std::string, CStaticMesh> Meshes;

	std::string WindowName{ "Name" };


	std::vector<CStaticMesh*> Objects;


	ID3D11Buffer* VertexBuffer;


	class CCamera* SelectedCamera{ nullptr };


	/// temp

	float TempRotation{ 0.0f };

	// TODO:
	// MOVE TO INPUT CLASS
	//MSG Message{ 0 };
public:
	//inline MSG GetMsg() const { return Message; }

public:
	/// Constructors.

	// Constructor, Default.
	CRenderer(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CRenderer();




	/// Functions

private:
	HRESULT Initialise();
	
	void DeleteAllMeshes();

public:

	void AddMesh(CStaticMesh* Mesh);

	void DeleteMesh(CStaticMesh* Mesh);


	/// Setters 

	SShader SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath = true);

	// Sets a specified camera to be the view camera.
	// @param Camera - The camera to view from.
	inline void SetCamera(class CCamera* Camera) { SelectedCamera = Camera; }


	void DrawAll();
};