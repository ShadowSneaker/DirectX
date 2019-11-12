#include "Floor.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Colliders/BoxComponent.h"


CFloor::CFloor(SObjectBase Base)
	:CWorldObject::CWorldObject{ Base }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	Mesh->SetMesh("Cube.obj");
	Mesh->SetShader("Shaders.hlsl");

	BoxCollider = CreateComponent<CBoxComponent>();
}