#pragma once
#include "../../WorldObject.h"



// An objecct type that gets fired in a direction and does damage to anything it hits.
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