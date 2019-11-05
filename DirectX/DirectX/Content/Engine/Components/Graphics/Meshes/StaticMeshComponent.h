#pragma once
#include "../../Component.h"
#include "../../../Graphics/Meshes/StaticMesh.h"


class CStaticMeshComponent :public CComponent, public CStaticMesh
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Default.
	CStaticMeshComponent(SComponentInfo Info);

	// Destructor.
	virtual ~CStaticMeshComponent() override;



	/// Functions


	/// Setters

	// Sets this mesh to use a specified shader.
	void SetShader(String FilePath, bool UseDefaultPath = true);

	// Applies an inputted texture onto this mesh.
	void SetTexture(String FilePath, bool UseDefaultPath = true);
};