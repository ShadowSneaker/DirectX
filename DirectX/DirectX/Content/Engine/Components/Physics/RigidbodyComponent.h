#pragma once
#include "../Component.h"
#include "../../Math/Physics/Rigidbody.h"


// Enables physics simulation on this object.
class CRigidbodyComponent :public CComponent, public CRigidbody
{


public:
	/// Constructors

	// Constructor, Default.
	CRigidbodyComponent(SComponentInfo Info);

	// Destructor.
	~CRigidbodyComponent();


	/// Functions


	void AttachCollider(class CCollider* InCollider);
};