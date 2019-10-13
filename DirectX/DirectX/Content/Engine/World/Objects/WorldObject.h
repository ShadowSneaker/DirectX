#pragma once
#include "ObjectBase.h"
#include "../../Math/Math.h"
#include "../../Core/Systems/Time.h"


class CWorldObject :public CObjectBase
{
private:

	/// Properties


public:
	// Note: This will likely be changed in the future, As the location, rotation and scale should be ecpasulated in a transform class.

	SVector Location;

	SQuaternion Rotation;

	SVector Scale;


public:
	/// Constructors

	// Constructor, Default.
	CWorldObject();


};