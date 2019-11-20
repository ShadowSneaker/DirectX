#pragma once
#include "../Component.h"
#include "../../Math/Physics/Rigidbody.h"


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