#include "SphereComponent.h"
#include "../../Math/Physics/Physics.h"


CSphereComponent::CSphereComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CSphereCollider::CSphereCollider{}
{
	GetPhysics()->AddCollider(this);
}


CSphereComponent::~CSphereComponent()
{
	GetPhysics()->RemoveCollider(this);
}