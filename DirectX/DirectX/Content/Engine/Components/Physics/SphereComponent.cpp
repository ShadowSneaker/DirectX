#include "SphereComponent.h"
#include "../../Math/Physics/Physics.h"
#include "../../World/Objects/WorldObject.h"
#include "..//Graphics/Meshes/StaticMeshComponent.h"


CSphereComponent::CSphereComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CSphere::CSphere{}
{
	GetPhysics()->AddCollider(this);
	CSphere::Owner = CComponent::GetOwner();
}


CSphereComponent::~CSphereComponent()
{
	GetPhysics()->RemoveCollider(this);
}