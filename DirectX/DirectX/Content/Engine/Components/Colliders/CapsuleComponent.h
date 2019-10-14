#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/CapsuleCollider.h"


class CCapsuleComponent :public CComponent, public CCapsuleCollider
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Initiates the capsule collider.
	CCapsuleComponent(SComponentInfo Info);

	// Destructor.
	~CCapsuleComponent();


	/// Functions
};