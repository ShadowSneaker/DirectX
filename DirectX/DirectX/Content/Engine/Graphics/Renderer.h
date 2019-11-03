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
	SVector4 DirectionalLight;
	SVector4 LightColour;
	SVector4 AmbiantLight;
};




class CRenderer
{
private:
	/// Properties

	const std::string ModelFilePath{ "Content/Assets/Shaders/" };
	const std::string TextureFilePath{ "Content/Assets/Images/" };


	std::map<std::string, STexture*> Textures;


	CWindow* Window;
	CDirectXSetup* Setup;

	// A list of all the shaders loaded.
	//std::map<std::string, CStaticMesh> Meshes;

	// The name of the aplicatoin window.
	std::string WindowName{ "Name" };


	// A list of static meshes to render.
	std::vector<CStaticMesh*> Objects;

	// A list of all lights in the world.
	std::vector<class CLightBase*> Lights;


	ID3D11Buffer* VertexBuffer;
	ID3D11SamplerState* Sampler;


	class CCamera* SelectedCamera{ nullptr };


	/// temp

	class CDirectionalLight* DirectionalLight;

public:

	// The amount of light that is equally applied to all faces.
	SVector4 AmbiantColour{ 1.0f, 1.0f, 1.0f, 1.0f };
	float AmbiantLightStregth{ 0.1f };


public:
	/// Constructors.

	// Constructor, Default.
	CRenderer(HINSTANCE HandleInstance, int CommandShow);

	// Destructor.
	~CRenderer();




	/// Functions

private:
	HRESULT Initialise();
	
	// Safely deletes all static meshes in memory.
	void DeleteAllMeshes();

	// Safely deletes all textures in memory.
	void DeleteAllTextures();

public:

	void AddMesh(CStaticMesh* Mesh);

	void DeleteMesh(CStaticMesh* Mesh);


	/// Setters 

	SShader SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath = true);

	STexture* SetTexture(std::string FilePath, bool UseDefaultPath = true);

private:
	bool AddTexture(SFilePath File);
public:

	// Sets a specified camera to be the view camera.
	// @param Camera - The camera to view from.
	inline void SetCamera(class CCamera* Camera) { SelectedCamera = Camera; }


	void DrawAll();
};