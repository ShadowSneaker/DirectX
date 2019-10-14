#pragma once
#include "Collider.h"


class CRigidBody
{
private:
	/// Properties



public:
	CCollider* Collider;


public:
	/// Constructors

	// Constructor, Initiates the rigid body with an attached collider.
	// @param InCollider - A reference to the collider that this rigid body uses.
	CRigidBody(CCollider* InCollider);
};