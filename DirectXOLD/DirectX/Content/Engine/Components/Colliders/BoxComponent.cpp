#include "BoxComponent.h"
#include"../../Math/Physics/Physics.h"


CBoxComponent::CBoxComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CBoxCollider::CBoxCollider{}
{
	GetPhysics()->AddCollider(this);
}


CBoxComponent::~CBoxComponent()
{
	GetPhysics()->RemoveCollider(this);
	CCollider::~CCollider();
	CBoxCollider::~CBoxCollider();
}