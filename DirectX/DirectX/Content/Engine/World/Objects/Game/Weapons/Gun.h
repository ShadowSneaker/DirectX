#pragma once
#include "../../WorldObject.h"


class CGun :public CWorldObject
{
private:
	/// Properties

	class CStaticMeshComponent* Body;

	class CObjectPool* BulletPool;


	uint ClipSize{ 10 };

	uint BulletsRemaining{ 10 };


public:
	/// Constructors

	// Constructor, Default.
	CGun(SObjectBase Base);

	// Destructor.
	~CGun();



	/// Overridables

	virtual void Begin() override;

	
	/// Functions

	void Fire();
};