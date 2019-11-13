#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Sphere.h"


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