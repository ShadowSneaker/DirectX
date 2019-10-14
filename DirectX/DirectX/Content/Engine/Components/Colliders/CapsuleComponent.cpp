#include "CapsuleComponent.h"
#include "../../Math/Physics/Physics.h"


CCapsuleComponent::CCapsuleComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCapsuleCollider::CCapsuleCollider{}
{
	GetPhysics()->AddCollider(this);
}


CCapsuleComponent::~CCapsuleComponent()
{
	GetPhysics()->RemoveCollider(this);
}