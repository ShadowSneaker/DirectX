#pragma once
#include "../../World/Objects/WorldObject.h"
#include "../Meshes/Shaders.h"

// http://aranna.altervista.org/data2/3d_game_programming_with_DirectX11.pdf#page=262&zoom=100,0,5

class CLightBase
{
protected:
	/// Properties

	//SShader Shader;

	// The amount of ambient light emmited by the light source.
	SVector4 Ambient = 0.01f;

	// The amount of diffuse light emmited by the light source.
	SVector4 Diffuse = 1.0f;

	// The amount of specular light emmited by the light source.
	SVector4 Specular = 1.0f;
	
public:

	// The location, rotation and scale of this light.
	STransform Transform;

	// How strong this light effects the world.
	// The colour this light will shine onto all objects.
	SVector4 Colour{ 1.0f, 1.0f, 1.0f, 1.0f };
	
	// How strong this light emmits.
	float Strength{ 1.0f };

	// Determines if this light applies shadows.
	bool CastShadow{ true };

	// Calculates the shadows during runtime instead of static.
	bool CastDynamicShadows{ true };


public:
	/// Construction

	// Constructor, Default.
	CLightBase();


	/// Functions


	/// Getters


	//INLINE SShader GetShader() const { return Shader; }
};