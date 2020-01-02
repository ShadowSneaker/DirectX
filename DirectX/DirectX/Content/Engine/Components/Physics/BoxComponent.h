#pragma once
#include "../Component.h"
#include "../../Math/Physics//Primitives/Box.h"


// A box collider that can be attached to world objects.
class CBoxComponent :public CComponent, public CBox
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