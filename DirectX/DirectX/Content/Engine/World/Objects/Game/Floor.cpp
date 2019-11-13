#include "Floor.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Colliders/BoxComponent.h"


CFloor::CFloor(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Plane.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->SetColour(SColour::Cyan());

	BoxCollider = CreateComponent<CBoxComponent>();
	BoxCollider->Extents = SVector{ 1.0f, 0.01f, 1.0f };
}