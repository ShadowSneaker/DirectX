#pragma once
#include "../Component.h"
#include "../../Math/Physics//Primitives/BoxCollider.h"


class CBoxComponent :public CComponent, public CBoxCollider
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Initiates a box collider.
	CBoxComponent(SComponentInfo Info);

	// Destructor.
	~CBoxComponent();


	/// Functions
};