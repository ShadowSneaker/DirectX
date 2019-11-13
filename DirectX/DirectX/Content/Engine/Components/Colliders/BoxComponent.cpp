#include "BoxComponent.h"
#include"../../Math/Physics/Physics.h"


CBoxComponent::CBoxComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CBox::CBox{}
{
	GetPhysics()->AddCollider(this);
	CBox::Owner = CComponent::GetOwner();
}


CBoxComponent::~CBoxComponent()
{
	GetPhysics()->RemoveCollider(this);
	CCollider::~CCollider();
	CBox::~CBox();
}