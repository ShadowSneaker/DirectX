#pragma once
#include <map>
#include <string>
#include <vector>

#include "../Math/DataTypes/Vertex.h"
#include "DirectXSetup.h"
#include "../Core/Systems/FileManager.h"
#include "Meshes/StaticMesh.h"
#include "../Math/DataTypes/Matrix.h"

#include "Meshes/Material.h"


struct SCBuffer
{
	SMatrix4 ViewMatrix;
	SVector4 DirectionalLight;
	SVector4 LightColour;
	SVector4 AmbiantLight;
};


struct SReflectBuffer
{
	SMatrix4 ViewMatrix;
	SMatrix4 WorldMatrix;
};


struct SCBPerFrame
{
	SDirectionalLight DirectionalLight;
	SPointLight PointLight;
	SSpotLight SpotLight;
	SVector EyePosW;
};


struct SCBPerObject
{
	SMatrix4 World;
	SMatrix4 WorldInvTranspose;
	SMatrix4 WorldViewProj;
	SMaterial Material;
};




class CRenderer
{
private:
	/// Properties


	// A list of textures that this renderer has created.
	// This is used to allow multiple objects to use the same texture without needing to create multiple copies of the texture.
	std::map<std::string, STexture*> Textures;

	// A reference to the created window.
	CWindow* Window{ nullptr };

	// A reference to the created DirectX setup.
	CDirectXSetup* Setup{ nullptr };

	// A reference to the created vertex buffer.
	//ID3D11Buffer* VertexBuffer{ nullptr };

	// A reference to the created sampler state.
	ID3D11SamplerState* Sampler{ nullptr };


	// The name of the aplicatoin window.
	std::string WindowName{ "Name" };

	// A list of static meshes to render.
	std::vector<CStaticMesh*> Objects;

	// A list of all lights in the world.
	std::vector<class CLightBase*> Lights;

	// A list of all camera references in the world.
	std::vector<class CCamera*> Cameras;

	// A reference to the camera the world should be viewd through.
	class CCamera* SelectedCamera{ nullptr };



	ID3D11RasterizerState* Raster{ nullptr };
	ID3D11DepthStencilState* RasterDepth{ nullptr };


	/// temp

	// TEMPORARY
	// A reference to the created directiona light
	// This should be removed into a component for world objects so I could have more than one directional light.
	class CDirectionalLight* DirectionalLight{ nullptr };

	// I don't like having a set font declared inside the renderer. This is a quick setup just to get font loaded on the screen.
	// Prferbally I'd createa UI system which could house a font type allowing text.
	class CFont* ScoreText{ nullptr };

public:
	// I have found out that when I spawn objects it will draw that object after the skybox thus I need to this here.
	// Personally I'd like to have the skybox always drawn last and this is the only way I can think to do it for the moment.
	CStaticMesh* SkyBox{ nullptr };


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
	
	// Safely deletes all static meshes in memory.
	void DeleteAllMeshes();

	// Safely deletes all textures in memory.
	void DeleteAllTextures();

	// Updates all objects visuals in the world.
	void UpdateObjects() ;

	// Updates all the lights in the world.
	void UpdateLights() const;

public:
	// Adds a created static mesh object to this class.
	// @param Mesh - The static mesh reference to add.
	void AddMesh(CStaticMesh* Mesh);

	// Removes a static mesh object from this class.
	// @note - Mesh referance is not deleted from memory.
	// @param Mesh - A reference to the static mesh to be removed.
	void RemoveMesh(CStaticMesh* Mesh);

	// Safely deletes the reference of a static mesh and removes it from this class if applicable.
	// @param Mesh - A referance to the static mesh to be deleted.
	void DeleteMesh(CStaticMesh* Mesh);

	// Adds a camera to this renderer.
	// @param Camera - A reference to the camera to add to this class.
	void AddCamera(class CCamera* Camera);

	// Removes a camera from this renderer.
	// @note - Camera reference is not deleted from memory.
	// @param Camera - The camera reference to remove from this class.
	void RemoveCamera(class CCamera* Camera);

	// Safely deletes the reference of a camera and removes it from this class if applicable.
	// @param Camera - The camera reference to delete.
	void DeleteCamera(class CCamera* Camera);

	// Adds a light to this renderer.
	// @param Light - A reference to the light to be added to this class.
	void AddLight(class CLightBase* Light);

	// Removes a light from this renderer.
	// @note - Light reference is not deleted from memory.
	// @param Light - The light reference to be removed.
	void RemoveLight(class CLightBase* Light);

	// Deletes a light from this renderer.
	// @param Light - The light reference to be deleted.
	void DeleteLight(class CLightBase* Light);

	// Draws all the objects stored within this class.
	// Note: does not draw disabled objects.
	void DrawAll();

	// Draws the specified static mesh object onto the screen.
	void RenderObject(CStaticMesh* Mesh);



	/// Setters 

	// Sets a specified shader onto the inputted object.
	// @param Mesh - The static mesh that the shader should be applied on.
	// @param FilePath - The location in files to the specific shader.
	// @param UseDefaultPath - Should the file path start at the default path for shaders.
	// @return - Returns the compiled shader.
	SShader SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath = true);

	// Sets a specific shader onto the inputted light object.
	// @param Light - The object that the shader should be applied on.
	// @param FilePath - The location in files to the specific shader.
	// @param useDefaultPath - Should the file path start at this default path for shaders.
	SShader SetLightShader(CLightBase* Light, std::string FilePath, bool UseDefaultPath = true);

	// Creates and returns a reference to a texture for an object.
	// Note - There will only be one version of the texture created in this class.
	// @param FilePath - The location in files to the specific texture.
	// @param UseDefaultPath - Should the file path start at the default path for textures.
	// @return - A reference to the created texture.
	STexture* SetTexture(std::string FilePath, bool UseDefaultPath = true);

	void SetFaceDirection(CStaticMesh* Mesh);

private:
	// Creates a texture and stores it within this class if the texture doesn't already exist.
	// @param File - The file path information to the texture.
	// @return - Returns true if the file was created.
	bool AddTexture(SFilePath File);
public:

	// Sets a specified camera to be the view camera.
	// @param Camera - The camera to view from.
	inline void SetCamera(class CCamera* Camera) { SelectedCamera = Camera; }

	

	/// Getters

	inline CWindow* GetWindow() const { return Window; }

	inline ID3D11Device* GetDevice() const { return Setup->GetDevice(); }

	inline class CFont* GetScoreText() const { return ScoreText; }
};