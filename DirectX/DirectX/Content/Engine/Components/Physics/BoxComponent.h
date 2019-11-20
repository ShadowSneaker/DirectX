#pragma once
#include "../Component.h"
#include "../../Math/Physics//Primitives/Box.h"


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