#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/PolygonCollider.h"


class CPolygonComponent :public CComponent, public CPolygonCollider
{
private:
	/// Properties


public:
	/// Constructors

	// Constructor, Initiates the polygon collider.
	CPolygonComponent(SComponentInfo Info);

	// Destructor.
	~CPolygonComponent();


	/// Functions
};