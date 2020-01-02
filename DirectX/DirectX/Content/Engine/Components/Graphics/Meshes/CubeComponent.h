#pragma once
#include "../../Component.h"
#include "../../../Graphics/Meshes/Primitives/Cube.h"



// A static mesh with a cube built in.
// @note - The mesh can be changed.
class CCubeComponent :public CComponent, public CCube
{
private:
	/// Components



public:
	/// Constructors

	// Constructor, Default.
	CCubeComponent(SComponentInfo Info);

	// Destructor.
	virtual ~CCubeComponent() override;



	/// Functions


	/// Setters

	// Sets this mesh to use a specified shader.
	void SetShader(String FilePath, bool UseDefaultPath = true);

	// Applies an inputted texture onto this mesh.
	void SetTexture(String FilePath, bool UseDefaultPath = true);
};