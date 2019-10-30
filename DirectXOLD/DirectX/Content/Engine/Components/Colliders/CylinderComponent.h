#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/CylinderCollider.h"


class CCylinderComponent :public CComponent, public CCylinderCollider
{
private:
	/// Properties



public:
	/// Constructors

	// Constructor, Initiates the cylinder collider.
	CCylinderComponent(SComponentInfo Info);

	// Destructor.
	~CCylinderComponent();


	/// Functions
};