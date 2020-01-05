#pragma once
#include "../WorldObject.h"



// A base object to represent as the floor.
class CFloor :public CWorldObject
{
private:
	/// Properties

	// The static mesh the floor has.
	class CStaticMeshComponent* Mesh;

	// The box collider around the floor.
	class CBoxComponent* BoxCollider;


public:
	/// Constructor.

	// Constructor, Default.
	CFloor(SObjectBase Base);



	/// Getters

	// Returns the static mesh.
	class CStaticMeshComponent* GetMesh() const;
};