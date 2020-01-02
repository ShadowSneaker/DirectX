#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Sphere.h"


// A sphere collider that can be attached to world objects.
class CSphereComponent :public CComponent, public CSphere
{
private: 
	/// Properties


public:
	/// Components

	// Constructor, Initiates the circle collider.
	CSphereComponent(SComponentInfo Info);

	// Destructor.
	~CSphereComponent();


	/// Functions
};