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
	~CStaticMeshComponent();



	/// Functions

}