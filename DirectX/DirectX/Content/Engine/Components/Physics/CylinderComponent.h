#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Cylinder.h"


// A cylinder collider that can be attached to world objects.
class CCylinderComponent :public CComponent, public CCylinder
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