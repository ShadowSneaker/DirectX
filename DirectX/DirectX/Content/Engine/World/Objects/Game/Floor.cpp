#include "Floor.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Physics/BoxComponent.h"


CFloor::CFloor(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	//Mesh->SetTexture("PavementCobbleAlbedo.tif");
	Mesh->SetTexture("SnowCliffs Albedo.png");
	Mesh->SetMesh("Plane.obj");
	Mesh->SetShader("Shaders.hlsl");

	BoxCollider = CreateComponent<CBoxComponent>();
	BoxCollider->Transform.SetParent(&Transform);
	BoxCollider->Extents = SVector{ 4.0f, 0.01f, 4.0f };
}


CStaticMeshComponent* CFloor::GetMesh() const
{ return Mesh; }