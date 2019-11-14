#pragma once
#include "../DataTypes/Vector.h"


class CRigidbody
{
private:
	/// Properties

	// A reference to the attached collider.
	class CCollider* Collider{ nullptr };



public:


	// How much influence gravity has on this object.
	float GravityScale{ 1.0f };

	// The directional momentum this object has.
	SVector Velocity{ 0.0f };



public:
	/// Constructors

	// Constructor, Default.
	CRigidbody();
};