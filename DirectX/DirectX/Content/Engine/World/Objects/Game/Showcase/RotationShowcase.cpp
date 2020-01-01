#include "RotationShowcase.h"
#include "../../../../Components/Graphics/Meshes/StaticMeshComponent.h"



CRotationShowcase::CRotationShowcase(SObjectBase Core)
	:CWorldObject::CWorldObject{ Core }
{
	Mesh = CreateComponent<CStaticMeshComponent>();
	//Mesh->SetTexture("NeatStoneWallAlbedo.tif");
	Mesh->SetTexture("PavementCobbleAlbedo.tif");
	Mesh->SetMesh("Sphere.obj");
	Mesh->SetShader("Shaders.hlsl");
	Mesh->Transform.SetParent(&Transform);
}


void CRotationShowcase::Update()
{
	Transform.Rotation[RotationAxis] += RotationSpeed * TTime::DeltaTime;
}