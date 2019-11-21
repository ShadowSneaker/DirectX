#pragma once
#include "../../World/Objects/WorldObject.h"


class CLightBase
{
public:
	/// Properties

	STransform Transform;

	// How strong this light effects the world.
	float Strength{ 1.0f };

	// The colour this light will shine onto all objects.
	SVector4 Colour{ 0.0f, 1.0f, 0.0f, 1.0f };

	// Determines if this light applies shadows.
	bool CastShadow{ true };

	// Calculates the shadows during runtime instead of static.
	bool CastDynamicShadows{ true };


public:
	/// Construction

	// Constructor, Default.
	CLightBase();


	/// Functions
};