#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/SphereCollider.h"


class CSphereComponent :public CComponent, public CSphereCollider
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