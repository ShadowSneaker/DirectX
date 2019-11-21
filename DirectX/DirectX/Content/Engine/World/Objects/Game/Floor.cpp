#include "Floor.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Physics/BoxComponent.h"


CFloor::CFloor(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Plane.obj");
	//Mesh->SetTexture("images.jpg");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->SetColour(SColour::Green());

	BoxCollider = CreateComponent<CBoxComponent>();
	BoxCollider->Transform.SetParent(&Transform);
	BoxCollider->Extents = SVector{ 1.0f, 0.01f, 1.0f };
}


CStaticMeshComponent* CFloor::GetMesh() const
{ return Mesh; }