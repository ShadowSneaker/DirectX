#pragma once
#include <map>
#include <string>
#include <vector>

#include "../Math/DataTypes/Vertex.h"
#include "DirectXSetup.h"
#include "../Core/Systems/FileReader.h"
#include "Meshes/StaticMesh.h"





//struct SObjectCluster
//{
//	/// Properties
//
//	// A reference to the mesh to be drawn.
//	class CStaticMesh* Mesh{ nullptr };
//
//	// The file path to this shader.
//	// Used as the key for getting the shader.
//	//SFilePath FilePath;
//
//	// The shader this object uses.
//	SShader* Shader;
//};




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
	HRESULT Initialise();
	
	void DeleteShaders();


public:

	// A safe way to add clusters to the renderer.
	// Creates a cluster while making sure that the shader has been created.
	// If the shader does not exist, then it will be created here.
	// @param Mesh - The static mesh that should be drawn.
	// @param ShaderFilePath - The file location for the shader this object will use.
	// @param UseDefaultPath - Should this use the default file path to find the shader.
	void AddCluster(CStaticMesh* Mesh, std::string ShaderFilePath, bool UseDefaultPath = true);

	SShader SetShader(CStaticMesh* Mesh, std::string FilePath, bool UseDefaultPath = true);

	void DrawAll();
};