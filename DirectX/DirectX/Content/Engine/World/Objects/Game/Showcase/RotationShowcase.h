#pragma once
#include "../../WorldObject.h"



// This is just a showcase class used to show the parent/child relationship between objects.
class CRotationShowcase :public CWorldObject
{
private:
	/// Properties

	// The mesh component.
	class CStaticMeshComponent* Mesh;

public:
	// Determines how fast this object rotates.
	float RotationSpeed{ 1.0f };

	EAxis RotationAxis{ EAxis::X };
	


public:
	/// Constructors 

	// Constructor, Default.
	CRotationShowcase(SObjectBase Core);



	/// Overridables

	// Runs every frame.
	virtual void Update() override;



	/// Getters

	// Returns the reference to the attached static mesh component.
	INLINE class CStaticMeshComponent* GetMesh() const { return Mesh; }
};