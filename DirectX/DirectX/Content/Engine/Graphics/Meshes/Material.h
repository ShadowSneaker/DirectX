#pragma once
#include "../../Math/DataTypes/Vector.h"


struct SMaterial
{
	// The amount of ambient light emmited by the material.
	SVector4 Ambient;
	
	// The amount of diffuse light scattered by the material
	SVector4 Diffuse;
	
	// The amount of specular light
	SVector4 Specular;

	// How much light is reflected off of this material.
	SVector4 Reflect;
};


struct SDirectionalLight
{
	// The amount of ambient light emmited by the light source.
	SVector4 Ambient;

	// The amount of diffuse light emmited by the light source.
	SVector4 Diffuse;

	// The amount of specular light emmited by the light source.
	SVector4 Specualr;

	// What way the light source is pointing.
	SVector Direction;

	// Padding bytes.
	float Pad;
};


struct SPointLight
{
	// The amount of ambient light emmited by the light source.
	SVector4 Ambient;

	// The amount of diffuse light emmited by the light source.
	SVector4 Diffuse;

	// The amount of specular light emmited by the light source.
	SVector4 Specualr;

	// The location of the center of the light source.
	SVector Position;

	// How far the light source will go.
	float Range;

	// Stores three constants in the format (a0, a1, a2) that control how light intensity falls off with distance.
	SVector Att;

	// Padding bytes.
	float Pad;
};


struct SSpotLight
{
	// The amount of ambient light emmited by the light source.
	SVector4 Ambient;

	// The amount of diffuse light emmited by the light source.
	SVector4 Diffuse;

	// The amount of specular light emmited by the light source.
	SVector4 Specualr;

	// The location of the center of the light source.
	SVector Position;

	// How far the light source will go.
	float Range;

	// What way the light source is pointing.
	SVector Direction;

	// The radius of the circle at the end of the spotlight.
	float Spot;

	// Stores three constants in the format (a0, a1, a2) that control how light intensity falls off with distance.
	SVector Att;

	// Padding bytes.
	float Pad;
};