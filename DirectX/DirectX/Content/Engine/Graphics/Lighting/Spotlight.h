#pragma once
#include "LightBase.h"


// A light type whichs represents a cone pointing in the direction of this light.
class CSpotlight :public CLightBase
{
private:
	/// Properties

	// Stores three constants in the format (a0, a1, a2) that control how light intensity falls off with distance.
	SVector Att;

public:

	// The furthest point circle radius.
	float Radius;

	// How far this light goes.
	float Range;


public:
	CSpotlight();
};