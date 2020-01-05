#pragma once
#include "../../WorldObject.h"
#include "../../../../Math/Physics/Physics.h"



// A simple class used to give the player points.
class CCoin :public CWorldObject
{
private:
	/// Properties

	// The mesh of the coin.
	class CStaticMeshComponent* Mesh;

	// The collider of the coin.
	class CSphereComponent* SphereCollider;

public:
	// A reference to the player.
	class CPlayer* Player;

	// Determines how much points the player will retreive when this coin is collected.
	uint Value{ 1 };



public:
	/// Constructors

	// Constructor, Default.
	CCoin(SObjectBase Core);



	/// Functions

	// Runs when the player collides with the coin.
	void CollisionEnter(SCollision Collision);
};