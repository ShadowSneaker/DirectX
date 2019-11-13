#include "CylinderComponent.h"
#include "../../Math/Physics/Physics.h"


CCylinderComponent::CCylinderComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CCylinder::CCylinder{}
{
	GetPhysics()->AddCollider(this);
	CCylinder::Owner = CComponent::GetOwner();
}


CCylinderComponent::~CCylinderComponent()
{
	GetPhysics()->RemoveCollider(this);
}