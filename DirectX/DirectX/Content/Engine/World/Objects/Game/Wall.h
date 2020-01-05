#pragma once
#include "../WorldObject.h"



// A basic object type that reprensets a wall in the game.
class CWall :public CWorldObject
{
private:
	/// Properties

	// The 3D model of the wall.
	class CStaticMeshComponent* Mesh;

	// The box collider.
	class CBoxComponent* BoxCollider;



public:
	/// Constructors

	// Constructor, Default.
	CWall(SObjectBase Core);

	

	/// Getters

	// Returns the static mesh.
	INLINE class CStaticMeshComponent* GetMesh() const { return Mesh; }
};