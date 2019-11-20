#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Cylinder.h"


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