#pragma once
#include "../../WorldObject.h"


class CBullet :public CWorldObject
{
private:
	/// Properties



public:
	/// Constructors

	// Constructor, Default.
	CBullet(SObjectBase Base);

	// Destructor.
	~CBullet();
};