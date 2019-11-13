#include "CapsuleComponent.h"
#include "../../Math/Physics/Physics.h"


CCapsuleComponent::CCapsuleComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCapsule::CCapsule{}
{
	GetPhysics()->AddCollider(this);
	CCapsule::Owner = CComponent::GetOwner();
}


CCapsuleComponent::~CCapsuleComponent()
{
	GetPhysics()->RemoveCollider(this);
}