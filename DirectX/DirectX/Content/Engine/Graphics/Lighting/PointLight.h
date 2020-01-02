#pragma once
#include "LightBase.h"

#include <DirectXMath.h>



// A light type which illuminates light in a sphere around the origin.
class CPointLight :public CLightBase
{
private:
	/// Properties

	// Stores three constants in the format (a0, a1, a2) that control how light intensity falls off with distance.
	SVector Att;


public:
	// How large the area this light should effect.
	float Radius{ 1.0f };

	// How far away the light should start fading away.
	float Falloff{ 1.0f };



public:
	/// Constructors

	// Constructor, Default.
	CPointLight();
};