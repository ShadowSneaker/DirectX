#include "Wall.h"
#include "../../../Components/Graphics/Meshes/StaticMeshComponent.h"
#include "../../../Components/Physics/BoxComponent.h"



CWall::CWall(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	//Mesh->SetTexture("PavementCobbleAlbedo.tif");
	Mesh->SetTexture("NeatStoneWallAlbedo.tif");
	Mesh->SetMesh("Wall.obj");
	Mesh->SetShader("Shaders.hlsl");

	BoxCollider = CreateComponent<CBoxComponent>();
	BoxCollider->Transform.SetParent(&Transform);
	BoxCollider->Extents = SVector{ 0.2f, 4.0f, 4.0f };
}