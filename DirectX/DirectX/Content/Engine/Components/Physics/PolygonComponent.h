#pragma once
#include "../Component.h"
#include "../../Math/Physics/Primitives/Polygon.h"


// An abiguous collider type that takes the shape of the static mesh attached.
class CPolygonComponent :public CComponent, public CPolygon
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