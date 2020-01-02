#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Capsule.h"


// A capsule collider that can be attached to world objects.
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