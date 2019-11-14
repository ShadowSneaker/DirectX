#include "SphereComponent.h"
#include "../../Math/Physics/Physics.h"
#include "../../World/Objects/WorldObject.h"
#include "..//Graphics/Meshes/StaticMeshComponent.h"


CSphereComponent::CSphereComponent(SComponentInfo Info)
	:CComponent::CComponent{ Info }, CSphere::CSphere{}
{
	GetPhysics()->AddCollider(this);

	//CStaticMeshComponent* Mesh = GetOwner()->FindComponent<CStaticMeshComponent>();
	//if (Mesh)
	//{
	//	uint Count = Mesh->VertexCount;
	//
	//	Vertices = &Mesh->Vertices;
	//	VertexCount = &Mesh->VertexCount;
	//	UpdateBounds();
	//}
	CSphere::Owner = CComponent::GetOwner();
}


CSphereComponent::~CSphereComponent()
{
	GetPhysics()->RemoveCollider(this);
}