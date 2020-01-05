#pragma once
#include "../../WorldObject.h"



//A gun type that shoots projectiles in the direction it is pointing.
class CGun :public CWorldObject
{
private:
	/// Properties

	// The static mesh of the gun.
	class CStaticMeshComponent* Body;

	// The object pool for all the gun's bullets.
	class CObjectPool* BulletPool;

	// How many bullets are in a clip.
	uint ClipSize{ 10 };

	// The current amount of bullets in the clip.
	uint BulletsRemaining{ 10 };



public:
	/// Constructors

	// Constructor, Default.
	CGun(SObjectBase Base);

	// Destructor.
	~CGun();



	/// Overridables

	// Runs when this object is created.
	virtual void Begin() override;

	

	/// Functions

	// Fires a bullet from this gun.
	void Fire();
};