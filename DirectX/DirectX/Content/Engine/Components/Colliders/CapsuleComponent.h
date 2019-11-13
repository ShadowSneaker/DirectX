#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Capsule.h"


class CCapsuleComponent :public CComponent, public CCapsule
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