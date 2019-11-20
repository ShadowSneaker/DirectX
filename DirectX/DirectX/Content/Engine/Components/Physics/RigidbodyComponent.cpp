#include "RigidbodyComponent.h"
#include "../../Math/Physics/Physics.h"


CRigidbodyComponent::CRigidbodyComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CRigidbody::CRigidbody{}
{
	
}


CRigidbodyComponent::~CRigidbodyComponent()
{

}


void CRigidbodyComponent::AttachCollider(CCollider* InCollider)
{
	GetPhysics()->AttachRigidbody(InCollider, this);
}