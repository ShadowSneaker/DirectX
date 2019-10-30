#include "CylinderComponent.h"
#include "../../Math/Physics/Physics.h"


CCylinderComponent::CCylinderComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCylinderCollider::CCylinderCollider{}
{
	GetPhysics()->AddCollider(this);
}


CCylinderComponent::~CCylinderComponent()
{
	GetPhysics()->RemoveCollider(this);
}